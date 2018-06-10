#include <iostream>
#include <string>

#include "piece.h"
#include "helpers.h"
#include "matrix.h"

using namespace std;

/*
Piece constructor with name, label, # of patterns and initial pattern
Initialize the piece with all its patterns, by rotating the initial pattern 'patternsCount' number
of time
*/
Piece::Piece(
    const std::string& name,
    const std::string& label, 
    long patternsCount,
    const Matrix& initialPattern
): _name(name), _label(label) {
    // Add all patterns for the piece, by rotating the initial pattern
    // Patterns are (rows, columns) pattern
    push_back(initialPattern);
    for (int i = 1; i < patternsCount; i++) {
        push_back(back().rot90());
    }
}

void Piece::generatePositions(int rows, int columns) {
    Matrix position(rows, columns);

}

/*
Operator << overload for Piece class
*/
std::ostream& operator<<(std::ostream& out, const Piece& p) {
    const char underline = char(238);
    const char block = char(219);
    const char space = *" ";
    const char newline = *"\n";
    string header;

    header = p._name + " (" + p._label + ")";

    out << header << newline;
    for (auto c: header) out << underline;
    for (auto pattern: p) {
        out << newline;
        for (auto row: pattern) {
            out << space;
            for (auto col: row) out << (col == 1 ? block : space);
            out << newline;
        }
    }
    out << newline;

    return out;
}

