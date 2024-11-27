//
// Created by 123 on 07/07/2024.
//
#include "Dense.h"

Matrix Dense::operator() (const Matrix &m)const
{//Applies the layer on the input and returns an output matrix
  return _activation_func(_weights*m +_bias);
}
