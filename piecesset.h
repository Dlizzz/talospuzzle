#pragma once
#include <list>
#include <memory>
#include <vector>
#include <string>

#include "params.h"
#include "piece.h"
#include "piecesbag.h"

class PiecesSet: 
    public std::list<Piece> {
public:
    PiecesSet(const PiecesBag& bag, const Params& params);
    friend std::ostream& operator<<(std::ostream& out, const PiecesSet& set);

protected:
    std::string piecesHeaders;
    std::string piecesCount;
    std::string setId;
    void optimize();
};

