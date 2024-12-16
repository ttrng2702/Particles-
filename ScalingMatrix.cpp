#include "ScalingMatrix.h"

ScalingMatrix::ScalingMatrix(float scaleFactor) : Matrix(2, 2) {
    m_data[0][0] = scaleFactor;
    m_data[1][1] = scaleFactor;
}
