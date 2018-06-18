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
    const string& name,
    const string& color,
    int patternsCount,
    const Matrix& initialPattern
): 
    vector<Matrix>(1, initialPattern),
    name(name),
    _color(htmlColorNameToValues(color)), 
    _positions(make_shared<Positions>()) {
    
    // Add all patterns for the piece, by rotating the initial pattern
    // push_back(initialPattern);
    for (int i = 1; i < patternsCount; i++) {
        push_back(back().rot90());
    }
}

void Piece::_generatePositions(unsigned int rows, unsigned int columns) {
    unsigned int row, col, maxRow, maxCol;

    for (auto& pattern : (*this)) {
        if ((pattern.rows() > rows) || (pattern.columns() > columns)) { break; }
        maxRow = rows - pattern.rows();
        maxCol = columns - pattern.columns();
        for (row = 0; row <= maxRow; ++row) {
            for (col = 0; col <= maxCol; ++col) {
                Matrix position(rows, columns);
                position.paste(pattern, row, col);
                _positions->push_back(position);
            }
        }
    }
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

