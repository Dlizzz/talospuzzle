#include <iostream>
#include <string>
#include <unordered_map>

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
