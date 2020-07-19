//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_MPI_STENCIL_HPP
#define AMATH583_MPI_STENCIL_HPP

#include "Grid.hpp"
#include <mpi.h>

class mpiStencil { };


void update_halo(Grid& x) {
  int up = 0;
  int down = 1;

  size_t myrank = MPI::COMM_WORLD.Get_rank();
  size_t mysize = MPI::COMM_WORLD.Get_size();

  size_t const edge_size = x.num_x();

  if (myrank < mysize-1){
    MPI::COMM_WORLD.Sendrecv(&x(0, x.num_x()-1), edge_size, MPI::DOUBLE, myrank+1, down, &x(0, x.num_x()), edge_size, MPI::DOUBLE, myrank+1, up);
  }
  if (myrank > 0){
    MPI::COMM_WORLD.Sendrecv(&x(0, 1), edge_size, MPI::DOUBLE, myrank-1, up, &x(0, 0), edge_size, MPI::DOUBLE, myrank-1, down);
  }

}

Grid operator*(const mpiStencil& A, const Grid& x) {
  Grid y(x);

  update_halo(const_cast<Grid&>(x));

  for (size_t i = 1; i < x.num_x()-1; ++i) {
    for (size_t j = 1; j < x.num_y()-1; ++j) {
      y(i, j) = x(i,j) - (x(i-1, j) + x(i+1, j) + x(i, j-1) + x(i, j+1))/4.0;
    }
  }

  return y;
}


#endif // AMATH583_MPI_STENCIL_HPP
