// Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

// Insert Activation namespace here...
namespace activation{
    Matrix relu(const Matrix &m);
    Matrix softmax(const Matrix &m);
    //function which receives const matrix and returns matrix
    typedef Matrix (*ActivationFunc)(const Matrix&);
}









#endif //ACTIVATION_H