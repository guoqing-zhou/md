#include <mpi.h>
#include <stdio.h>
#include "md.h"

using namespace std;

MD::MD(int narg, char **arg, MPI_Comm communicator ){
  test=1;
  //io = new IO(this,"md.in");
  io = new IO(this, narg, arg, communicator);
  atom = new Atom(this, communicator);
  io->init();
}

MD::~MD(){
  delete io;
}
