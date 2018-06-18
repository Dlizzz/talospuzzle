#pragma once
#include <list>

#include "params.h"
#include "piece.h"
#include "piecesbag.h"

class PiecesSet: 
    public std::list<Piece> {
public:
    PiecesSet(const PiecesBag& bag, const Params& params);
    friend std::ostream& operator<<(std::ostream& out, const PiecesSet& set);

protected:
    void optimize();
};

