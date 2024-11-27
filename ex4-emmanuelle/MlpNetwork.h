// MlpNetwork.h
#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};

class MlpNetwork
{
 private:
  Dense _layer1;
  Dense _layer2;
  Dense _layer3;
  Dense _layer4;

 public:
  MlpNetwork(const Matrix weights[], const Matrix biases[])
      : _layer1(weights[0], biases[0], activation::relu),
        _layer2(weights[1], biases[1], activation::relu),
        _layer3(weights[2], biases[2], activation::relu),
        _layer4(weights[3], biases[3], activation::softmax){}
  digit operator()(const Matrix& m)const;


};

#endif // MLPNETWORK_H
