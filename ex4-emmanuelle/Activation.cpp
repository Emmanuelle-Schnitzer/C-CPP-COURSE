#include "Activation.h"
#include <cmath>
Matrix activation::relu(const Matrix &m){
  //does relu on each variable in matrix
  int rows = m.get_rows();
  int cols = m.get_cols();
  Matrix new_matrix = Matrix(rows,cols);
  for(int i=0;i<rows*cols;i++)
  {
    if(m[i] >= 0){
      new_matrix[i] = m[i];
    }
    else{
      new_matrix[i] =0;
    }
  }
  return new_matrix;
}

Matrix activation::softmax(const Matrix &m){
  //returns softmax of a vector
  Matrix new_matrix(m);
  float sum =0;
  for(int i=0;i<m.get_cols()*m.get_rows();i++){
    new_matrix[i] = std::exp(m[i]);
    sum += new_matrix[i];
  }
  float new_sum = 1/sum;
  return new_sum*new_matrix;
}