#ifndef TRANSLATIONMATRIX_H
#define TRANSLATIONMATRIX_H

#include "Matrix.h"

class TranslationMatrix : public Matrix {
public:
    TranslationMatrix(float dx, float dy);
};

#endif // TRANSLATIONMATRIX_H
