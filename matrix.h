#pragma once
#include <vector>
#include <string>
#include <iostream>

using MatrixLineDef = std::vector<unsigned char>;
using MatrixDef = std::vector<MatrixLineDef>;

class Matrix:
    public MatrixDef {
public:
    using MatrixDef::MatrixDef;
    Matrix() noexcept = default;
    Matrix(unsigned int ro, unsigned int col);
    bool addMaxOne(const Matrix& matrix);
    void paste(const Matrix& matrix, unsigned int toRow, unsigned int toCol);
    void combine(const Matrix& matrix, const char mask = 0);
    bool operator==(Matrix& matrix);
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
    std::string to_string(int offset);
    Matrix rot90() const;
    Matrix symHorizontal() const;
    Matrix symVertical() const;
    Matrix symCentral() const;
    Matrix times(const unsigned char factor);
    unsigned int rows() const;
    unsigned int columns() const;
};

// Helper function for 
bool equivalent(const Matrix& matrixA, const Matrix& matrixB);

inline unsigned int Matrix::rows() const { return size(); }
inline unsigned int Matrix::columns() const { return front().size(); }
