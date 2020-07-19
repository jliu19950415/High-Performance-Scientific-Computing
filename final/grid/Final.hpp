//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_FINAL_HPP
#define AMATH583_FINAL_HPP

#include <iostream>
#include "Grid.hpp"
#include "Stencil.hpp"
#include "mpiStencil.hpp"

#include <mpi.h>


double mpi_dot(const Grid& X, const Grid& Y) {
  double sum = 0.0;

  size_t myrank = MPI::COMM_WORLD.Get_rank();
  size_t mysize = MPI::COMM_WORLD.Get_size();

  size_t start = (myrank == 0?0:1);
  size_t stop = (myrank == (mysize - 1)?X.num_x():X.num_x()-1);

  // Parallelize me
  for (size_t i = start; i < stop; ++i){
    for (size_t j = 0; j < X.num_y(); ++j){
      sum += X(i, j) * Y(i, j);
    }
  }

  double const sigma = sum;

  MPI::COMM_WORLD.Allreduce(&sigma, &sum, 1, MPI::DOUBLE, MPI::SUM);

  return sum;
}


size_t jacobi(const mpiStencil& A, Grid& x, const Grid& b, size_t maxiter, double tol) {

  Grid y = b;
  swap(x, y);

  for (size_t iter = 0; iter < maxiter; ++iter) {

    double rho = 0;

    for (size_t i = 1; i < x.num_x() - 1; ++i) {
      for (size_t j = 1; j < x.num_y() - 1; ++j) {
	      y(i, j) = (x(i - 1, j) + x(i + 1, j) + x(i, j - 1) + x(i, j + 1)) / 4.0;
	      rho += (y(i, j) - x(i, j)) * (y(i, j) - x(i, j));
      }
    }

    double sigma = rho;
    MPI::COMM_WORLD.Allreduce(&sigma, &rho, 1, MPI::DOUBLE, MPI::SUM);

    if (MPI::COMM_WORLD.Get_rank() == 0){
      std::cout << "||r|| = " << std::sqrt(rho) << std::endl;
    }

    if (std::sqrt(rho) < tol) return iter;
  

    swap(x, y);


    // Perform halo exchange (write me)
    size_t myrank = MPI::COMM_WORLD.Get_rank();
    size_t mysize = MPI::COMM_WORLD.Get_size();

    size_t const edge_size = x.num_x();

    int up = 0;
    int down = 1;

    if (myrank < mysize - 1){
      MPI::COMM_WORLD.Sendrecv(&x(0, x.num_x() - 1), edge_size, MPI::DOUBLE, myrank+1, down, &x(0, x.num_x()), edge_size, MPI::DOUBLE, myrank+1, up);
    }

    if(myrank > 0){
      MPI::COMM_WORLD.Sendrecv(&x(0, 1), edge_size, MPI::DOUBLE, myrank-1, up, &x(0, 0), edge_size, MPI::DOUBLE, myrank-1, down);
    }

    
  }
    
  return maxiter;
}


// Parallelize me
size_t ir(const mpiStencil& A, Grid& x, const Grid& b, size_t max_iter, double tol) {
  for (size_t iter = 0; iter < max_iter; ++iter) {
    Grid r = b - A*x;

    double sigma = mpi_dot(r, r);

    if (MPI::COMM_WORLD.Get_rank() == 0) 
      std::cout << "||r|| = " << std::sqrt(sigma) << std::endl;
    if (std::sqrt(sigma) < tol) return iter;

    x += r;
  
  }
  return max_iter;
}


// Parallelize me
size_t cg(const mpiStencil& A, Grid& x, const Grid& b, size_t max_iter, double tol) {
  size_t myrank = MPI::COMM_WORLD.Get_rank();

  Grid r = b - A*x, p(b);
  double rho = mpi_dot(r, r), rho_1 = 0.0;

  for (size_t iter = 0; iter < max_iter; ++iter) {
    if (0 == myrank) {
      std::cout << iter << ": ||r|| = " << std::sqrt(rho) << std::endl;
    }

    if (iter == 0) {
      p = r;
    } else {
      double beta = (rho / rho_1);
      p = r +  beta * p;
    }
    
    Grid q = A*p;

    double alpha = rho / mpi_dot(p, q);
    
    x += alpha * p;
    
    rho_1 = rho;
    r -= alpha * q;
    rho = mpi_dot(r, r);

    if (rho < tol) return iter;
  }

  return max_iter;
}

#endif // AMATH583_FINAL_HPP
