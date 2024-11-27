#include "Matrix.h"
#include <iostream>
#include <cmath>
#include <cstring>

#define PRINT_NUM 0.01

Matrix& Matrix::transpose(){
  //returns a transposed matrix
  Matrix new_matrix(_cols,_rows);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++){
      new_matrix[j*_rows +i] =  _matrix_arr[i*_cols +j];
    }
  }
  _rows = new_matrix._rows;
  _cols = new_matrix._cols;
  std::memcpy(_matrix_arr, new_matrix._matrix_arr,
              _rows * _cols * sizeof(float));
  return *this;
}

Matrix& Matrix::vectorize(){
  //turns matrix to be 1 column and 1 row
  _rows *= _cols;
  _cols = 1;
  return *this;
}


Matrix Matrix::dot(const Matrix& m){
  //returns a new Matrix that is the element-wise multiplication (Hadamard
  // product) of
  //this matrix with another matrix m
  if (m._rows!=_rows || m._cols!=_cols) {
    throw std::invalid_argument("Number of rows and columns must be positive");
  }
  Matrix new_matrix(_rows,_cols);
  for (int i = 0; i < _rows*_cols; i++) {
      new_matrix._matrix_arr[i] = _matrix_arr[i] *
                                  m._matrix_arr[i];
    }
  return new_matrix;
}


void Matrix::plain_print() const
{//prints the matrix as a matrix
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      std::cout << _matrix_arr[i * _cols + j] << ' ';
    }
    std::cout << std::endl;
  }
}
float Matrix::norm () const
{//returns the norm of the matrix
  float sum = 0;
  for (int i = 0; i < _rows*_cols; i++) {
      sum += std::pow(_matrix_arr[i], 2);
    }

  return std::sqrt(sum);
}
float Matrix::sum () const
{//returns the sum of all values in matrix
  float sum = 0;
  for (int i = 0; i < _rows*_cols; i++) {
      sum += _matrix_arr[i];

  }
  return sum;
}
unsigned int Matrix::argmax () const
{//returns index of the largest number in the matrix.
  //In the case of a tie, return the lower index.
  float max = _matrix_arr[0];
  int max_index = 0;
  for (int i = 1; i < _rows*_cols; i++) {
    if(_matrix_arr[i] > max){
      max = _matrix_arr[i];
      max_index = i;
    }
  }
  return max_index;
}
Matrix &Matrix::operator+= (const Matrix &m)
{//adds to matrix values the values of another matrix
  for (int i = 0; i < _rows*_cols; i++) {
    _matrix_arr[i] = _matrix_arr[i] + m._matrix_arr[i];
    }
  return *this;
}
Matrix operator+ (const Matrix &a, const Matrix &b)
{//adds two matrix's
  if (a._rows!=b._rows || a._cols!=b._cols) {
    throw std::invalid_argument("Number of rows and columns must be positive");
  }
  Matrix new_matrix(a._rows,a._cols);
  for (int i = 0; i < a._rows*a._cols; i++) {
    new_matrix._matrix_arr[i] = a._matrix_arr[i] + b._matrix_arr[i];
  }
  return new_matrix;

}
Matrix& Matrix::operator=(const Matrix &m)
{//copies gotten matrix into this
  if (this !=&m || _rows != m._rows || _cols != m._cols)
  {
    const float * old_matrix = _matrix_arr;
    _matrix_arr = new float[m._rows * m._cols];
    delete[]old_matrix;
    _rows = m._rows;
    _cols = m._cols;
  }
  std::memcpy(_matrix_arr, m._matrix_arr, _rows * _cols * sizeof(float));
  return *this;
}
Matrix operator* (const Matrix &a, const Matrix &b)
{//multiplies two matrix's
  if (a._cols != b._rows) {
    throw std::invalid_argument("Matrix dimensions do not allow "
                                "multiplication");
  }
  Matrix new_matrix(a._rows,b._cols);
  for (int i = 0; i < a._rows; i++) {
    for (int j = 0; j < b._cols; j++){
      for(int s=0;s<a._cols;s++){
        new_matrix(i, j) += a(i, s) * b(s, j);
      }
    }
  }
  return new_matrix;
}
Matrix Matrix::operator*(float c)const
{//multiplies a matrix by a number, when this is the matrix
  Matrix new_matrix(_rows,_cols);
  for (int i = 0; i < _rows * _cols; i++)
  {
    new_matrix[i] = _matrix_arr[i]*c;
  }
  return new_matrix;
}
Matrix operator* (float c, const Matrix &m)
{//multiplies a matrix by a number
  Matrix new_matrix(m._rows,m._cols);
  for (int i = 0; i < m._rows * m._cols; i++)
  {
    new_matrix._matrix_arr[i] =m._matrix_arr[i] *c;
  }
  return new_matrix;
}

float& Matrix::operator() (int index1, int index2)
{//returns a setter for a position in matrix
  if (index1>=_rows || index2>=_cols) {
    throw std::invalid_argument("Number of rows and columns must be positive");
  }
  if (index1<0 || index2<0) {
    throw std::invalid_argument("Number of rows and columns must be positive");
  }
  return _matrix_arr[index1*_cols+index2];
}
const float &Matrix::operator() (int index1, int index2) const
{//returns a getter for a position in matrix
  if (index1>=_rows || index2>=_cols) {
    throw std::invalid_argument("Number of rows and columns must be positive");
  }
  if (index1<0 || index2<0) {
    throw std::invalid_argument("Number of rows and columns must be positive");
  }
  return _matrix_arr[index1*_cols+index2];
}

float& Matrix::operator[] (int index)
{//returns a setter for a position in matrix
  if (index>=_rows*_cols || index<0) {
    throw std::invalid_argument("Number of rows and columns must be positive");
  }
  return _matrix_arr[index];
}
const float &Matrix::operator[] (int index) const
{//returns a getter for a position in matrix
  if (index>=_rows*_cols || index<0) {
    throw std::invalid_argument("Number of rows and columns must be positive");
  }
  return _matrix_arr[index];
}
std::ostream &operator<< (std::ostream &s, const Matrix &m)
{
  float num;
  for (int i = 0; i < m._rows; i++) {
    for (int j = 0; j < m._cols; j++){
      num = m(i,j);
      if(num>PRINT_NUM){
        s << "**";
      }
      else{
        s << " ";
      }
    }
    s << std::endl;
  }
  return s;
}

std::istream &operator>> (std::istream &s,const Matrix &m){
  int len_mat = m._rows * m._cols;
  int buffer_size = len_mat * sizeof(float);

  // Ensure the stream is good before reading
  if (!s) {
    throw std::runtime_error("Stream is not good before reading.");
  }

  // Allocate buffer
  char *buffer = new char[buffer_size];
  s.read(buffer, buffer_size);

  // Check if read failed or didn't read enough data
  if (!s || s.gcount() != static_cast<std::streamsize>(buffer_size)) {
    delete[] buffer;
    throw std::runtime_error("Failed to read matrix data from stream");
  }

  // Cast the buffer to float* and populate the matrix
  auto *float_buffer = reinterpret_cast<float*>(buffer);
  for (int i = 0; i < len_mat; ++i) {
    m._matrix_arr[i] = float_buffer[i];
  }

  // Clean up buffer
  delete[] buffer;
  return s;
}

Matrix Matrix::rref() const {
  Matrix new_matrix = *this;
  int pos = 0;
  int num_rows = new_matrix._rows;
  int num_cols = new_matrix._cols;
  for (int current_row = 0; current_row < num_rows && pos < num_cols;
  ++current_row) {
    // Find the row with the leading non-zero element in the current column
    int row_with_pivot = current_row;
    while (new_matrix(row_with_pivot, pos) == 0) {
      ++row_with_pivot;
      if (row_with_pivot == num_rows) {
        row_with_pivot = current_row;
        ++pos;
        if (pos == num_cols) {
          return new_matrix;
        }
      }
    }
    // Swap rows if necessary
    if (row_with_pivot != current_row) {
      for (int col = 0; col < num_cols; ++col) {
        std::swap(new_matrix(row_with_pivot, col),
                  new_matrix(current_row, col));
      }
    }
    // Normalize the pivot row
    float pivot_value = new_matrix(current_row, pos);
    for (int col = 0; col < num_cols; ++col) {
      new_matrix(current_row, col) /= pivot_value;
    }
    // Eliminate column entries
    for (int target_row = 0; target_row < num_rows; ++target_row) {
      if (target_row != current_row) {
        float factor = -new_matrix(target_row, pos);
        for (int col = 0; col < num_cols; ++col) {
          new_matrix(target_row, col) += factor *
              new_matrix(current_row, col);
        }
      }
    }
    ++pos;
  }
  return new_matrix;
}



