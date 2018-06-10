#include <iostream>
#include <vector>

#include "matrix.h"
#include "errors.h"

using namespace std;

Matrix::Matrix() noexcept {}

Matrix::Matrix(unsigned int ro, unsigned int col): 
    vector<MatrixLineDef>(ro, MatrixLineDef(col, 0)) {}

Matrix Matrix::rot90() const {
    Matrix out;
    MatrixLineDef outLine;
    int inRow, inCol, outCol, outRow;

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
// greater than 1. 
// Function is index proof. If given matrix is too large, it will be only partially added. If given 
// origin for addition is outside boundaries, nothing will be added. 
// - const Matrix& matrix: the matrix to add
// - unsigned int toRow: row of the current matrix where to add the matrix
// - unsigned int toCol: col of the current matrix where to add the matrix
// - Return bool: false if the addition was not possible due to elements being greater than 1,
//   else true 
bool Matrix::add(const Matrix& matrix, unsigned int toRow, unsigned int toCol) {
    unsigned int row, col, matrixRow, matrixCol, minRows, minColumns;

    minRows = rows() <= matrix.rows() + toRow ? rows() : matrix.rows() + toRow;
    minColumns = columns() <= matrix.columns() + toCol ? columns(): matrix.columns() + toCol;
    
    // First test if there is no element > 1 after addition, without changing the matrix
    // Loop over the current matrix, to be sure that we stay within its boundaries
    for (row = toRow; row < minRows; ++row) {
        matrixRow = row - toRow;
        for (col = toCol; col < minColumns; ++col) {
            matrixCol = col - toCol;
            if (((*this)[row][col] + matrix[matrixRow][matrixCol]) > 1) return false;
        }
    }

    // Do the real addition
    for (row = toRow; row < minRows; ++row) {
        matrixRow = row - toRow;
        for (col = toCol; col < minColumns; ++col) {
            matrixCol = col - toCol;
            (*this)[row][col] += matrix[matrixRow][matrixCol];
        }
    }

    return true;
}

void Matrix::paste(const Matrix& matrix, unsigned int toRow, unsigned int toCol) {
    unsigned int row, col, matrixRow, matrixCol, minRows, minColumns;

    // Can't paste outside of the current matrix
    if ((toRow >= rows()) || (toCol >= columns())) return;

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

std::ostream& operator<<(std::ostream& out, const Matrix& m) {
    const char underline = char(238);
    const char block = char(219);
    const char empty = char(250);
    const char space = *" ";
    const char newline = *"\n";

    for (auto row: m) {
        out << space;
        for (auto col: row) out << (col == 1 ? block : empty);
        out << newline;
    }
    return out;
}
