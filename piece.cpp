#include <iostream>
#include <string>
#include <utility>

#include "piece.h"
#include "helpers.h"
#include "matrix.h"

using namespace std;

//Initialize the piece with all its patterns, by rotating the initial pattern 'patternsCount' number
//of time
Piece::Piece(
    const string& givenName,
    const int Id,
    const string& color,
    const Matrix& initialPattern
): 
    list<Matrix>(1, initialPattern),
    name(givenName),
    _Id(Id),
    _color(htmlColorNameToValues(color)), 
    _positions(make_unique<Positions>()) {
    
    // Add all patterns for the piece, by rotating the initial pattern
    for (int i = 1; i < 4; ++i) { push_back(back().rot90()); }
    // Deduplicate the list of patterns
    for (list<Matrix>::iterator patternIt = begin();
        patternIt != end();
        ++patternIt
    ) {
        list<Matrix>::iterator testedPatternIt = next(patternIt);
        while(testedPatternIt != end()) {
            if (*patternIt == *testedPatternIt) {
                testedPatternIt = erase(testedPatternIt);
                // Tested solution iterator now points to the solution after the deleted one
            }
            else {
                // Move to next solution
                ++testedPatternIt;

            }
        }
    }
}

Piece::Piece(const Piece& piece):
    std::list<Matrix>(piece),
    name(piece.name),
    _Id(piece._Id),
    _color(piece._color),
    _positions(make_unique<Positions>(*piece._positions)) {}

long Piece::_generatePositions(unsigned int rows, unsigned int columns) {
    for (auto& pattern : (*this)) {
        // Skip to next pattern if dimensions don't match
        if ((pattern.rows() > rows) || (pattern.columns() > columns)) { continue; }
        unsigned int maxRow = rows - pattern.rows();
        unsigned int maxCol = columns - pattern.columns();
        for (unsigned int row = 0; row <= maxRow; ++row) {
            for (unsigned int col = 0; col <= maxCol; ++col) {
                Matrix position(rows, columns);
                position.paste(pattern, row, col);
                _positions->push_back(position);
            }
        }
    }

    return _positions->size();
}

//Operator << overload for Piece class
ostream& operator<<(ostream& out, const Piece& piece) {
    const auto underline = char(238);
    const char newline = *"\n";
    string header;

    header = piece.name;

    out << header << newline;
    out << string(header.size(), underline);
    for (auto& pattern: piece) {
        out << newline << pattern;
    }
    out << newline;

    return out;
}

