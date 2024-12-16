#ifndef ROTATIONMATRIX_H
#define ROTATIONMATRIX_H

#include "Matrix.h"
#include <cmath>

class RotationMatrix : public Matrix {
public:
    RotationMatrix(float angle);
};

#endif // ROTATIONMATRIX_H
