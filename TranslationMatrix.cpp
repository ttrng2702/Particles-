#include "TranslationMatrix.h"

TranslationMatrix::TranslationMatrix(float dx, float dy) : Matrix(3, 3) {
    m_data[0][0] = 1;
    m_data[1][1] = 1;
    m_data[2][2] = 1;

    m_data[0][2] = dx;
    m_data[1][2] = dy;
}
