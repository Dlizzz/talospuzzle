#include <iostream>
#include <iomanip>
#include <list>
#include <iterator>
#include <memory>
#include <string>
#include <sstream>
#include <filesystem>
#include <ctime>
#include <locale>

#if defined(_WIN32)
#include <codeanalysis\warnings.h>
#include <CppCoreCheck\Warnings.h>
#endif
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#pragma warning ( disable: ALL_CPPCORECHECK_WARNINGS)
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <boost/asio/ip/host_name.hpp>
#pragma warning( pop )

#include "errors.h"
#include "params.h"
#include "board.h"
#include "piece.h"
#include "piecesset.h"
#include "puzzle.h"
#include "solution.h"
#include "helpers.h"

using namespace std;
namespace fs = boost::filesystem;

Puzzle::Puzzle(const Params& params): 
    Board(params.getRows(), params.getColumns()),
    PiecesSet(piecesBag, params),
    _verbose(params.getVerbose()), 
    _first(params.getFirst()), 
    _stats(params.getStats()),
    _combinationsCount(1),
    _puzzleId("P" + boardId + setId),
    _solvingTime(),
    _solutions(make_unique<list<Solution>>()) {
        
    // Verify that there is enough piece tocover the board
    unsigned long piecesSurface = size() * 4;
    unsigned long boardSurface = boardRows * boardColumns;
    if (piecesSurface > boardSurface) {
        string message = "Too many pieces for the board. Have "
            + to_string(size())
            + ", needs "
            + to_string(boardSurface / 4);
        throw ErrorParams(message);
    }
    else if (piecesSurface < boardSurface) {
        string message = "Not enough pieces for the board. Have "
            + to_string(size())
            + ", needs "
            + to_string(boardSurface / 4);
        throw ErrorParams(message);
    }

    for (auto& piece : *this) { 
        _combinationsCount *= piece._generatePositions(boardRows, boardColumns); 
    }

    if (_verbose) {
        cout << "Puzzle board: " << boardRows << " rows x " << boardColumns << " columns\n";
        cout << "Pieces set:\n";
        for (auto& piece : *this) {
            cout << "  - " << piece.name << " with " << piece.getPositionsCount() << " positions\n";
        }
        cout << "Combinations count: " << _combinationsCount << endl;
    }
}

void Puzzle::solve() {

    if (_verbose) {
        cout << "Solving puzzle... ";
    }
    _solvingTime = clock();

    // Reorder the set of pieces to allow a maximum of parallel threads and to optimize
    // tree crawling.
    optimize();

    // Each position of the first piece (front) is a tree root.
    Positions* positions = front()._positions.get();
    
    for (Positions::iterator positionsIt = positions->begin(); 
        positionsIt < positions->end(); 
        ++positionsIt
    ) {
        // Initialize solution, using current position as root node
        PiecesSet::iterator pieceIt = begin();
        Solution solution(pieceIt, positionsIt, *positionsIt);
        
        // Recursively crawl the tree of positions to build solutions
        _crawlTree(solution, ++pieceIt);

        // Exit immediatly, if requested and if we have found the first solution
        if (_first && (_solutions->size() == 1)) { break; }
    }

    // Remove duplicated solution, 
    // including rotated and symetrical solutions (horizontal, vertical, central)
    _deduplicateSolutions();

    _solvingTime = clock() - _solvingTime;
    if (_verbose) {
        cout << "in " << (float)_solvingTime / CLOCKS_PER_SEC << " seconds." << endl;
    }
}

void Puzzle::_crawlTree(Solution& solution, PiecesSet::iterator& nextPieceIt) {

    // If we have already reached the end of the tree, it means tha we have only one piece
    // Then each position is a solution 
    if (nextPieceIt == end()) { 
        _solutions->push_back(solution);
        return; 
    }

    // Backup the puzzle board
    Matrix backupBoard = *solution._board;
    
    // Test current node with all positions of next piece in the set
    Positions* positions = (*nextPieceIt)._positions.get();

    for (Positions::iterator positionsIt = positions->begin(); 
        positionsIt < positions->end(); 
        ++positionsIt
    ) {
        // Exit immediatly, if requested, if we have found the first solution
        if (_first && (_solutions->size() == 1)) { return; }

        // If we have a valid (no overloap) combination of positions. Add it to the solution.
        if (solution._board->addMaxOne(*positionsIt)) {
            solution.push_back(make_pair(nextPieceIt, positionsIt));
            // We have a final solution if we have reached the end of the tree
            if (nextPieceIt == prev(end())) {
                _solutions->push_back(solution);
            }
            // Else we are on a valid path, move to next piece
            else {
                _crawlTree(solution, ++nextPieceIt); 
                // Going back to current piece
                --nextPieceIt;
            }
            // Restore tree path to current node
            solution.pop_back();
            // Restore the puzzle board
            *solution._board = backupBoard;
        }
    }
}

void Puzzle::printSolutions() {

    if (_solutions->size() == 0) {
        cout << "No solution to the puzzle!\n";
        return;
    }

    int solutionId = 1;
    for (auto& solution : *_solutions) {
        // Draw the solution
        string header = "Solution " + to_string(solutionId) + "\n";
        cout << header << string(header.size(), UNDERLINE) << "\n";
        solution.print(1);
        cout << endl;
        ++solutionId;
    }

    if (_stats) { _printStats(); }
}

void Puzzle::_deduplicateSolutions() {

    // Generate the solutions board with pieces Id for deduplication
    for (auto& solution : *_solutions) {
        solution._makeSolutionBoard();
    }
    
    // Deduplicate the list of solutions
    for (list<Solution>::iterator solutionIt = _solutions->begin();
        solutionIt != _solutions->end();
        ++solutionIt
    ) {
        list<Solution>::iterator testedSolutionIt = next(solutionIt);
        while(testedSolutionIt != _solutions->end()) {
            if (*solutionIt == *testedSolutionIt) {
                testedSolutionIt = _solutions->erase(testedSolutionIt);
                // Tested solution iterator now points to the solution after the deleted one
            }
            else {
                // Move to next solution
                ++testedSolutionIt;

            }
        }
    }

    // Generate the solutions board with pieces Index for drawing
    for (auto& solution : *_solutions) {
        solution._makeSolutionBoard(*this);
    }
}

void Puzzle::_printStats() const {
    fs::path statsFilename = fs::current_path() / "talos-puzzle-stats.csv";
    fs::ofstream statsFile;

    try {
        if (!fs::exists(statsFilename)) {
            string headers = "Hostname;Date;Id;Rows;Columns;"
                + piecesHeaders
                + ";Combinations;Solutions;Elapsed Time";
            // Output file header
            statsFile.open(statsFilename);
            statsFile << headers << endl;
        }
        else {
            statsFile.open(statsFilename, fs::ofstream::app);
        }

        stringstream timeStamp;
        auto t = time(nullptr);
        timeStamp << put_time(localtime(&t), "%d/%m/%Y %H:%M:%S");
        
        stringstream elapsedTime;
        locale currentLocale("");
        elapsedTime.imbue(currentLocale);
        elapsedTime << ((float)_solvingTime / CLOCKS_PER_SEC);

        string record =
            boost::asio::ip::host_name()
            + ";"
            + timeStamp.str()
            + ";"
            + _puzzleId
            + ";"
            + to_string(boardRows)
            + ";"
            + to_string(boardColumns)
            + ";"
            + piecesCount
            + ";"
            + to_string(_combinationsCount)
            + ";"
            + to_string(_solutions->size())
            + ";"
            + elapsedTime.str();

        statsFile << record << endl;
        statsFile.close();
    }
    catch (fs::filesystem_error& e) {
        throw ErrorParams(e.what());
    }
}