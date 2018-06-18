#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "matrix.h"
#include "helpers.h"

enum asciiBackgroundColor {
    ASCII_BG_RED = 41,
    ASCII_BG_GREEN,
    ASCII_BG_YELLOW,
    ASCII_BG_BLUE,
    ASCII_BG_MAGENTA,
    ASCII_BG_CYAN,
    ASCII_BG_WHITE
};

using Positions = std::vector<Matrix>;

class Piece: 
    public std::vector<Matrix> {
public:
    std::string name;
    Piece(
        const std::string& name,
        const std::string& color,
        int patternsCount,
        const Matrix& initialPattern
    );
    const int getPositionsCount() const noexcept { return _positions->size(); }
    const ColorValues getColor() const noexcept { return _color; }
    friend class Puzzle;
    friend std::ostream& operator<<(std::ostream& out, const Piece& piece);
    friend bool comparePiece(const Piece& a, const Piece& b) noexcept;
    
private:
    ColorValues _color;
    std::shared_ptr<Positions> _positions;
    void _generatePositions(unsigned int rows, unsigned int columns);
};

// Sorting helper. Piece 'a' < Piece 'b', if Piece 'a' has less positions
inline bool comparePiece(const Piece& a, const Piece& b) noexcept { 
    return a._positions->size() < b._positions->size();
}


