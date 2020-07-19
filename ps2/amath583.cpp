//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "amath583.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include <cmath>
#include <cstddef>

void zeroize(Vector &x) {
  for (size_t i = 0; i < x.num_rows(); ++i){
    x(i) = 0;
  }
}

double one_norm(const Vector& x) {
  // WRITE ME
  double sum = 0.0;
  for (size_t i = 0; i < x.num_rows(); ++i){
    sum += std::abs(x(i));
  }

  return sum;
}

double two_norm(const Vector& x) {
  // WRITE ME
  double sum = 0.0;
  for (size_t i = 0; i < x.num_rows(); ++i){
    sum += std::pow(x(i),2.0);
  }
  sum = std::sqrt(sum);
  return sum;
}

double inf_norm(const Vector& x) {
  double result = 0.0;
  double temp = 0.0;
  for (size_t i = 0; i < x.num_rows(); ++i){
    temp = std::abs(x(i));
    if(temp > result){
      result = temp;
    }
  }

  return result;
}

double dot(const Vector& x, const Vector& y) {
  // WRITE ME
  double result = 0.0;
  double pairwise = 0.0;
  // add assertion for length checking?
  for (size_t i = 0; i < x.num_rows(); ++i){
    pairwise = x(i) * y(i);
    result += pairwise;
  }
  return result;
}

double two_norm_d(const Vector& x) { 
  return std::sqrt(dot(x,x));
}

double one_norm(const Matrix& A) {
  double sum = 0.0;
  for (size_t j = 0; j < A.num_cols(); ++j) {    // for each column
    double tmp = 0.0;
    for (size_t i = 0; i < A.num_rows(); ++i) {    // compute column sum
      tmp += std::abs(A(i, j));
    }
    sum = std::max(sum, tmp);
  }
  return sum;
}


double inf_norm(const Matrix& A) {
  double sum = 0.0;
  for (size_t i = 0; i < A.num_rows(); ++i){
    double tmp = 0.0;
    for(size_t j = 0; j < A.num_cols(); ++j){
      tmp += std::abs(A(i,j));
    }
    sum = std::max(sum, tmp);
  }
  return sum;
}

// WRITE ME f_norm()
double f_norm(const Matrix& A){
  double result = 0.0;
  for (size_t i = 0; i < A.num_rows(); ++i){
    for(size_t j = 0; j < A.num_cols(); ++j){
      result += std::pow(A(i,j),2.0);
    }
  }

  result = std::sqrt(result);
  return result;
}
