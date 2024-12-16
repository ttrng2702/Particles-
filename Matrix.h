#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

class Matrix {
public:
    Matrix(int rows, int cols);
    virtual ~Matrix() {}

    float& operator()(int row, int col);
    Matrix operator*(const Matrix& other) const;

    void print() const;

    int getRows() const { return m_rows; }
    int getCols() const { return m_cols; }

private:
    int m_rows, m_cols;
    std::vector<std::vector<float>> m_data;
};

#endif // MATRIX_H
