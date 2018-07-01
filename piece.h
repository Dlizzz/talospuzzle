#pragma once
#include <iostream>
#include <string>
#include <list>
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
    public std::list<Matrix> {
public:
    // Members
    std::string name;
    // Standard methods
    Piece(
        const std::string& givenName,
        const int Id,
        const std::string& color,
        const Matrix& initialPattern
    );
    Piece(const Piece& piece);
    // Methods
    long getPositionsCount() const noexcept { return _positions->size(); }
    int getId()  const noexcept { return _Id; }
    const ColorValues getColor() const noexcept { return _color; }
    // Friends
    friend class Puzzle;
    friend std::ostream& operator<<(std::ostream& out, const Piece& piece);
    friend bool comparePiece(const Piece& a, const Piece& b) noexcept;
    
private:
    // Members
    int _Id;
    ColorValues _color;
    std::unique_ptr<Positions> _positions;
    // Methods
    long _generatePositions(unsigned int rows, unsigned int columns);
};

// Sorting helper. Piece 'a' < Piece 'b', if Piece 'a' has less positions
inline bool comparePiece(const Piece& a, const Piece& b) noexcept { 
    return a._positions->size() < b._positions->size();
}


