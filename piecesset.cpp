#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include "piecesset.h"
#include "piece.h"
#include "params.h"

using namespace std;

PiecesSet::PiecesSet(const PiecesBag& bag, const Params& params):
    piecesHeaders(), 
    piecesCount(),
    setId() {

    stringstream id;
    for (auto& piece : bag) {
        int pieceCount = params.getPieceCount(piece.first);
        piecesHeaders += (piece.first + ";");
        piecesCount += (to_string(pieceCount) + ";");
        id << setw(2) << setfill('0') << pieceCount;
        for (int i = 0; i < pieceCount; i++) { push_back(piece.second); }
    }
    piecesHeaders.pop_back();
    piecesCount.pop_back();
    setId = id.str();
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
