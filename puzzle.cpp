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

}
