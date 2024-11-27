// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <cstring>

// You don't have to use the struct. Can help you with MlpNetwork.h
struct matrix_dims {
    int rows, cols;
};


class Matrix{
  //pointer to a flat array that describes a matrix
  int _rows;
  int _cols;
  float * _matrix_arr;
 public:
  //constructor
  Matrix(int rows,int cols):_rows(rows), _cols(cols),
  _matrix_arr(nullptr) {
    if (rows <= 0 || cols <= 0){
      throw std::invalid_argument("Number of rows and "
                                  "columns must be positive");
    }
    _matrix_arr =new float[rows * cols];
    // Initialize array elements to zero
    std::fill(_matrix_arr, _matrix_arr + rows * cols, 0.0F);
  }
  Matrix()
      : _rows(1), _cols(1), _matrix_arr(new float[1])
      {_matrix_arr[0] = 0;}
  Matrix(const Matrix& m)
      : _rows(m._rows), _cols(m._cols),
      _matrix_arr(new float[m._rows * m._cols]) {
    std::memcpy(_matrix_arr, m._matrix_arr, _rows * _cols * sizeof(float));
  }
  ~Matrix(){delete[] _matrix_arr;}//destructor
  int get_rows() const{return _rows;}
  int get_cols() const{return _cols;}
  Matrix& transpose();
  Matrix& vectorize();
  void plain_print() const;
  Matrix dot(const Matrix& m);
  float norm() const;
  Matrix rref() const;
  unsigned int argmax() const;
  float sum() const;
  Matrix& operator+=(const Matrix& m);
  friend Matrix operator+(const Matrix& a,const Matrix& b);
  Matrix& operator=(const Matrix& m);
  friend Matrix operator*(const Matrix& a,const Matrix& b);
  Matrix operator*(float c)const;//c on the right
  friend Matrix operator*(float c, const Matrix &m);//c on the left
  float& operator()(int index1, int index2);
  const float& operator()(int index1, int index2)const;
  float& operator[](int index);
  const float& operator[](int index)const;
  friend std::ostream& operator<<(std::ostream& s, const Matrix &m);
  friend std::istream& operator>>(std::istream& s,const Matrix &m);

};



#endif //MATRIX_H