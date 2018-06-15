#pragma once
#include <vector>

#include "params.h"
#include "piecesbag.h"
#include "piece.h"

class PiecesSet: 
    public std::vector<Piece> {
public:
    PiecesSet(const PiecesBag& bag, const Params& params);
    friend std::ostream& operator<<(std::ostream& out, const PiecesSet& set);

protected:
    void optimize();
};

