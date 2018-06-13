#include <algorithm>
#include <iostream>
#include <string>

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


// Sort the set of pieces from the lowest number of positions to the biggest
// then put the biggest first. It allows to have the maximum of parallel threads and to optimize
// tree crawling.
void PiecesSet::optimize() {
    sort(begin(), end(), sortPiece);
    auto it = insert(begin(), back());
    pop_back();
}

ostream& operator<<(ostream& out, const PiecesSet& set) {
    const char newline = *"\n";
    string header;

    for (auto piece : set) {
        header = piece.getName() + " (" + piece.getLabel() + "):\t"
            + to_string(piece.getPositions()->size()) + " positions";
        out << header << newline;
    }

    return out;
}
