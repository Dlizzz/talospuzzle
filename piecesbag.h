#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

#include "piece.h"

typedef std::unordered_map<std::string, Piece> PiecesDef;

class PiecesBag: 
    public PiecesDef  {
public:
    using PiecesDef::PiecesDef;
    friend std::ostream& operator<<(std::ostream &out, const PiecesBag &bag);
};

extern PiecesBag piecesBag;