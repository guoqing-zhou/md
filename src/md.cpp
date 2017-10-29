#include <mpi.h>
#include <stdio.h>
#include "md.h"

using namespace std;

MD::MD(int narg, char **arg, MPI_Comm){
  //io = new IO(this,"md.in");
  io = new IO(this, arg[1]);
  io->init();
}

MD::~MD(){
  delete io;
}
