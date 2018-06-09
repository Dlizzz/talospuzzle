#pragma once
#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::vector<int>> Pattern;
typedef std::vector<std::vector<int>> Position;

class Piece: 
    private std::vector<Pattern> {
public:
    Piece(
        const std::string &name, 
        const std::string &label, 
        long patternsCount,
        const Pattern &initialPattern
    );
    friend std::ostream& operator<<(std::ostream &out, const Piece &p);
    
private:
    std::string _name;
    std::string _label;
};

