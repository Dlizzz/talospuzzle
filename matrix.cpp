#include <iostream>
#include <vector>

#include "matrix.h"
#include "errors.h"

using namespace std;

Matrix::Matrix(unsigned int ro, unsigned int col): 
    MatrixDef(ro, MatrixLineDef(col, 0)) {}

Matrix Matrix::rot90() const {
    Matrix out;
    MatrixLineDef outLine;
    unsigned int inRow, inCol, outCol, outRow;

    // Current matrix columns become new matrix rows
    out.reserve(columns());
    for (outRow = 0; outRow < columns(); ++outRow) {
        outLine.clear();
        // Current matrix rows become new matrix columns
        outLine.reserve(rows());
        inCol = columns() - 1 - outRow;
        for (outCol = 0; outCol < rows(); ++outCol) {
            inRow = outCol;
            outLine.push_back((*this)[inRow][inCol]);
        }
        out.push_back(outLine);
    }
    
    return out;
}

// Add the given matrix to the current matrix, only if the addition doesn't lead to elements being
// greater than 1. Both matrixes must have same size.
// - const Matrix& matrix: the matrix to add
// - Return bool: false if the addition was not possible due to elements being greater than 1 or 
//   matrixes not from same size; In both cases current matrix stays unchanged.
bool Matrix::add(const Matrix& matrix) {
    unsigned int row, col;

    // Don't do anything if matrixes don't have same size
    if ((rows() != matrix.rows()) || (columns() != matrix.columns())) { return false; }
   
    // First test if there is no element > 1 after addition, without changing the matrix
    for (row = 0; row < rows(); ++row) {
        for (col = 0; col < columns(); ++col) {
            if (((*this)[row][col] + matrix[row][col]) > 1) { return false; }
        }
    }

    // Do the real addition
    for (row = 0; row < rows(); ++row) {
        for (col = 0; col < columns(); ++col) {
            (*this)[row][col] += matrix[row][col];
        }
    }

    return true;
}

// Paste (elements are replaced) the given matrix into the current matrix, at the given coordinates.
// Function is index proof. If given matrix is too large, it will be croped. If given coordinates
//  are outside current matrix boundaries, nothing will be pasted. 
// - const Matrix& matrix: the matrix to add
// - unsigned int toRow: row of the current matrix where to add the matrix
// - unsigned int toCol: col of the current matrix where to add the matrix
void Matrix::paste(const Matrix& matrix, unsigned int toRow, unsigned int toCol) {
    unsigned int row, col, matrixRow, matrixCol, minRows, minColumns;

    // Can't paste outside of the current matrix
    if ((toRow >= rows()) || (toCol >= columns())) { return; }

    minRows = rows() <= matrix.rows() + toRow ? rows() : matrix.rows() + toRow;
    minColumns = columns() <= matrix.columns() + toCol ? columns(): matrix.columns() + toCol;

    for (row = toRow; row < minRows; ++row) {
        matrixRow = row - toRow;
        for (col = toCol; col < minColumns; ++col) {
            matrixCol = col - toCol;
            (*this)[row][col] = matrix[matrixRow][matrixCol];
        }
    }
}

ostream& operator<<(ostream& out, const Matrix& m) {
    const auto block = char(219);
    const auto empty = char(250);
    const char space = *" ";
    const char newline = *"\n";

    for (auto row: m) {
        out << space;
        for (auto col : row) { out << (col == 1 ? block : empty); }
        out << newline;
    }
    return out;
}
