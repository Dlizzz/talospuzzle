#include <iostream>
#include <string>

#include "piece.h"
#include "helpers.h"

using namespace std;

/*
Piece constructor with name, label, # of patterns and initial pattern
Initialize the piece with all its patterns, by rotating the initial pattern 'patternsCount' number
of time
*/
Piece::Piece(
    const std::string &name,
    const std::string &label, 
    long patternsCount,
    const matrix &initialPattern
): _name(name), _label(label) {
    // Add all patterns for the piece, by rotating the initial pattern
    // Patterns are (rows, columns) matrix
    _patterns.push_back(initialPattern);
    for (int i = 1; i < patternsCount; i++) {
        _patterns.push_back(rot90(_patterns.back()));
    }
}

/*
<< operator overload for Piece class
*/
std::ostream& operator<<(std::ostream &out, const Piece& p) {
    out << p._name << " (" << p._label << ")";
    for (auto pattern : p._patterns) {
        out << "\n";
        for (auto row : pattern) {
            out << " |";
            for (auto col: row)
                out << (col == 1 ? "X" : " ") << " ";
            out << "\b|\n";
        }
    }
    out << "\n";
    return out;
}
