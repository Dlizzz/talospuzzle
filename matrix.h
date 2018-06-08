#pragma once
#include <vector>

template <class T> class Matrix {
public:
    Matrix(int rows, int columns);
    Matrix<T> rot90(Matrix<T> &in);
    T max(Matrix<T> &in);

private:
    std::vector<std::vector<T>> 
    int _rows;
    int _columns;
};
