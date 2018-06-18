#include <iostream>
#include <iomanip>
#include <list>
#include <iterator>
#include <memory>

#include "params.h"
#include "board.h"
#include "piece.h"
#include "piecesset.h"
#include "puzzle.h"
#include "solution.h"

using namespace std;

Puzzle::Puzzle(const Params& params): 
    Board(params.getRows(), params.getColumns()),
    PiecesSet(piecesBag, params),
    _verbose(params.getVerbose()), 
    _first(params.getFirst()), 
    _stats(params.getStats()),
    _solutions(make_unique<list<Solution>>()) {
        
    for (auto& piece : *this) { piece._generatePositions(boardRows, boardColumns); }
}

void Puzzle::solve() {
    // Reorder the set of pieces to allow a maximum of parallel threads and to optimize
    // tree crawling.
    optimize();

    // Each position of the first piece (front) is a tree root.
    shared_ptr<Positions> positions = front()._positions;
    
    for (Positions::iterator positionsIt = positions->begin(); 
        positionsIt < positions->end(); 
        ++positionsIt
    ) {
        PiecesSet::iterator pieceIt = begin();
        // Initialize solution, using current position as root node
        Solution solution(pieceIt, positionsIt, *positionsIt);
        cout << "Current: (0, ";
        cout << distance(positions->begin(), positionsIt) << ") / (";
        cout << size() - 1 << ", " << positions->size() - 1 << ")\n";
        
        // Recursively crawl the tree of positions to build solutions
        _crawlTree(solution, ++pieceIt);

        // Exit immediatly, if requested, if we have found the first solution
        if (_first && (_solutions->size() == 1)) { return; }
    }

    // Remove duplicated solution, including symetrical solutions (horizontal, vertical, central)
    //_deduplicateSolutions();
}

void Puzzle::_crawlTree(Solution& solution, PiecesSet::iterator& nextPieceIt) {
    // Backup the puzzle board
    Matrix backupBoard = *solution._board;
    
    // Test current node with all positions of next piece in the set
    shared_ptr<Positions> positions = (*nextPieceIt)._positions;

    for (Positions::iterator positionsIt = positions->begin(); 
        positionsIt < positions->end(); 
        ++positionsIt
    ) {
        // Exit immediatly, if requested, if we have found the first solution
        if (_first && (_solutions->size() == 1)) { return; }
        cout << string(distance(begin(), nextPieceIt) * 2, ' ');
        cout << "Next: (" << distance(begin(), nextPieceIt) << ", ";
        cout << distance(positions->begin(), positionsIt) << ") / (";
        cout << size() - 1 << ", " << positions->size() - 1 << ")\n";

        if (solution._board->addMaxOne(*positionsIt)) {
            // We have a valid (no overloap) combination of positions. Add it to the solution.
            solution.push_back(make_pair(nextPieceIt, positionsIt));
            cout << string(distance(begin(), nextPieceIt) * 2, ' ');
            cout << "=> Valid combination" << "\n";
            if (nextPieceIt == prev(end())) {
                // We have a solution
                _solutions->push_back(solution);
                cout << string(distance(begin(), nextPieceIt) * 2, ' ');
                cout << "=> Solution\n";
            }
            else {
                cout << string(distance(begin(), nextPieceIt) * 2, ' ');
                cout << "Current: (" << distance(begin(), nextPieceIt) << ", ";
                cout << distance(positions->begin(), positionsIt) << ") / (";
                cout << size() - 1 << ", " << positions->size() - 1 << ")\n";
                // We are on a valid path, move to next piece
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
    int solutionId = 0;
    for (auto& solution: *_solutions) {
        // Build puzzle board for the solution
        Matrix puzzleBoard(boardRows, boardColumns);
        for (auto& position : solution) {
            unsigned char pieceId = distance(begin(), position.first) + 1;
            puzzleBoard.combine(position.second->times(pieceId));
        }

        // Draw the solution
        string header = "Solution " + to_string(solutionId++); 
        cout << header << endl << string(header.size(), UNDERLINE) << endl;
        coutTopBorder(boardColumns, 1);
        cout << endl;
        for (auto& row : puzzleBoard) {
            coutSideBorder(1);
            for (auto& element : row) {
                // Get the piece color, from element being the index of the piece  
                ColorValues color = (*next(this->begin(), element - 1)).getColor();
                coutColoredBlock(color);
            }
            coutSideBorder(0);
            cout << endl;
        }
        coutBottomBorder(boardColumns, 1);
        cout << endl << endl;
    }
}

void Puzzle::_deduplicateSolutions() {
    for (auto& solution : *_solutions) {

        // Build puzzle board for the solution
        Matrix puzzleBoard(boardRows, boardColumns);
        for (auto& position : solution) {
            unsigned char pieceId = distance(begin(), position.first) + 1;
            puzzleBoard.combine(position.second->times(pieceId));
        }
    }
}
