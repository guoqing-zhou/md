#include <mpi.h>
#include <stdio.h>
#include "md.h"

using namespace std;

MD::MD(int narg, char **arg, MPI_Comm){
  io = new IO(this,"md.in");
  io->init();
}

MD::~MD(){
  delete io;
}