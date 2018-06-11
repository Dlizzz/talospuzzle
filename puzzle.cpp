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
    _verbose(params.getVerbose()), _first(params.getFirst()), _stats(params.getStats()) {

    for (auto piece : *this) piece.generatePositions(boardRows, boardColumns);
}

void Puzzle::solve() {
    optimize();

    for (auto piece : *this)
        cout << setw(9) << left << piece.getName() << ":" << piece.getPositions()->size() 
        << " positions\n";
}
