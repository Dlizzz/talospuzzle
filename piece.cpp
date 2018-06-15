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
    const string& label, 
    long patternsCount,
    const Matrix& initialPattern
): _name(name), _label(label), _positions(new vector<Matrix>) {
    
    // Add all patterns for the piece, by rotating the initial pattern
    push_back(initialPattern);
    for (int i = 1; i < patternsCount; i++) {
        push_back(back().rot90());
    }
}

void Piece::generatePositions(unsigned int rows, unsigned int columns) {
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

    header = piece._name + " (" + piece._label + ")";

    out << header << newline;
    for (auto c : header) { out << underline; }
    for (auto& pattern: piece) {
        out << newline << pattern;
    }
    out << newline;

    return out;
}

