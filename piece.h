#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "matrix.h"


class Piece: 
    private std::vector<Matrix> {
public:
    Piece(
        const std::string& name, 
        const std::string& label, 
        long patternsCount,
        const Matrix& initialPattern
    );
    friend std::ostream& operator<<(std::ostream& out, const Piece& p);
    const std::vector<Matrix>& positions() const ;
    void generatePositions(int rows, int columns);
    
private:
    std::string _name;
    std::string _label;
    std::vector<Matrix> _positions;
};

inline const std::vector<Matrix>& Piece::positions() const { return _positions; }

