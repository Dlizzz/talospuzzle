#pragma once
#include <vector>

using MatrixLineDef = std::vector<unsigned char>;
using MatrixDef = std::vector<MatrixLineDef>;

class Matrix:
    public MatrixDef {
public:
    Matrix() noexcept = default;
    Matrix(unsigned int ro, unsigned int col);
    bool add(const Matrix& matrix);
    void paste(const Matrix& matrix, unsigned int toRow, unsigned int toCol);
    Matrix rot90() const;
    unsigned int rows() const;
    unsigned int columns() const;
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
};

inline unsigned int Matrix::rows() const { return size(); }
inline unsigned int Matrix::columns() const { return front().size(); }
