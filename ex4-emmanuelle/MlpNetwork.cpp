#include "MlpNetwork.h"


digit MlpNetwork::operator() (const Matrix &m)const
{//operator which returns balue of mltnetwork
  Matrix new_matrix(_layer4(_layer3(_layer2(_layer1(m)))));
  unsigned int max_index = new_matrix.argmax();
  return {max_index, new_matrix[max_index]};
}

