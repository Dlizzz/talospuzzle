#pragma once
#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::vector<int>> matrix;

class Piece {
public:
    Piece(
        const std::string &name, 
        const std::string &label, 
        long patternsCount,
        const matrix &initialPattern
    );
    friend std::ostream& operator<<(std::ostream &out, const Piece &p);
    
private:
    std::string _name;
    std::string _label;
    std::vector<matrix> _patterns;
};

