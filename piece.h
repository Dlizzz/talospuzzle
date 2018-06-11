#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "matrix.h"

class Piece: 
    public std::vector<Matrix> {
public:
    Piece(
        const std::string& name, 
        const std::string& label, 
        long patternsCount,
        const Matrix& initialPattern
    );
    friend std::ostream& operator<<(std::ostream& out, const Piece& piece);
    friend bool sortPiece(const Piece& a, const Piece& b) noexcept;
    std::shared_ptr<const std::vector<Matrix>> getPositions() const noexcept;
    const std::string& getName() const noexcept;
    const std::string& getLabel() const noexcept;
    void generatePositions(int rows, int columns);
    
private:
    std::string _name;
    std::string _label;
    std::shared_ptr<std::vector<Matrix>> _positions;
};

inline std::shared_ptr<const std::vector<Matrix>> Piece::getPositions() const noexcept { 
    return _positions; 
}
inline const std::string& Piece::getName() const noexcept { return _name; }
inline const std::string& Piece::getLabel() const noexcept { return _label; }

// Sorting helper. Piece 'a' < Piece 'b', if Piece 'a' has less positions
inline bool sortPiece(const Piece& a, const Piece& b) noexcept { 
    return a._positions->size() < b._positions->size();
}


