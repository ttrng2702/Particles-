#include "Matrix.h"

Matrix::Matrix(int rows, int cols) : m_rows(rows), m_cols(cols) {
    m_data.resize(rows, std::vector<float>(cols, 0));
}

float& Matrix::operator()(int row, int col) {
    return m_data[row][col];
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (m_cols != other.m_rows) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication.");
    }

    Matrix result(m_rows, other.m_cols);
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < other.m_cols; ++j) {
            result(i, j) = 0;
            for (int k = 0; k < m_cols; ++k) {
                result(i, j) += m_data[i][k] * other.m_data[k][j];
            }
        }
    }
    return result;
}

void Matrix::print() const {
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            std::cout << m_data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
