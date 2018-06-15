#include <iostream>
#include <iomanip>
#include "puzzle.h"
#include "piecesbag.h"
#include "board.h"
#include "piecesset.h"
#include "params.h"

using namespace std;

Puzzle::Puzzle(const Params& params): 
    Board(params.getRows(), params.getColumns()),
    PiecesSet(piecesBag, params),
    _verbose(params.getVerbose()), 
    _first(params.getFirst()), 
    _stats(params.getStats()),
    _treeDepth(size() - 1) {

    for (auto piece : *this) { piece.generatePositions(boardRows, boardColumns); }
}

void Puzzle::solve() {
    // Reorder the set of pieces to allow a maximum of parallel threads and to optimize
    // tree crawling.
    optimize();

    // Each position of the first piece is a tree root.
    for (auto position : *(front().getPositions())) {
        cout << position << "\n";
    }
}

void _crawlTree(std::vector<TreeNode>& _treePath, Matrix& puzzleBoard) {

}
