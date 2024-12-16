#include "RotationMatrix.h"

RotationMatrix::RotationMatrix(float angle) : Matrix(2, 2) {
    m_data[0][0] = cos(angle);
    m_data[0][1] = -sin(angle);
    m_data[1][0] = sin(angle);
    m_data[1][1] = cos(angle);
}
