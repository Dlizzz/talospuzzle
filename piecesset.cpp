#include <algorithm>

#include "piecesset.h"
#include "piece.h"
#include "params.h"

using namespace std;

PiecesSet::PiecesSet(const PiecesBag& bag, const Params& params) {
    int pieceCount;

    for (auto piece : bag) {
        pieceCount = params.getPieceCount(piece.first);
        for (int i = 0; i < pieceCount; i++) push_back(piece.second);
    }
}

// Sorting helper. Piece a <= Piece b if Piece A has less or equal number of positions
friend bool sortPiece(const Piece& a, const Piece& b) {

}

// Sort the set of pieces from the lowest number of positions to the biggest
// then put the biggest first. It allows to have the maximum of parallel threads and to optimize
// tree crawling.
void PiecesSet::optimize() {

}
