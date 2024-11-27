// Dense.h
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

// Insert Dense class here...
class Dense{
  Matrix _weights;
  Matrix _bias;
  activation::ActivationFunc _activation_func{nullptr};
 public:
  Dense(const Matrix &weights, const Matrix &bias,
        activation::ActivationFunc activation_func)
  :_weights(weights), _bias(bias),
    _activation_func(activation_func){}//constructor of class Dense
  Matrix get_weights()const {return _weights;}
  Matrix get_bias()const {return _bias;}
  activation::ActivationFunc get_activation()const {return _activation_func;}
  Matrix operator()(const Matrix &m)const;
};









#endif //DENSE_H