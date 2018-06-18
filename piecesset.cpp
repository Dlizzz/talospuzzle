#include <algorithm>
#include <iostream>
#include <string>

#include "piecesset.h"
#include "piece.h"
#include "params.h"

using namespace std;

PiecesSet::PiecesSet(const PiecesBag& bag, const Params& params) {
    for (auto& piece : bag) {
        int pieceCount = params.getPieceCount(piece.first);
        for (int i = 0; i < pieceCount; i++) { push_back(piece.second); }
    }
}


// Sort the set of pieces from the lowest number of positions to the biggest,
// then put the biggest first. 
void PiecesSet::optimize() {
    sort(comparePiece);
    auto it = insert(begin(), back());
    pop_back();
}

ostream& operator<<(ostream& out, const PiecesSet& set) {
    const char newline = *"\n";

    for (auto& piece : set) {
        string header = piece.name + ":\t" + to_string(piece.getPositionsCount()) + " positions";
        out << header << newline;
    }

    return out;
}
