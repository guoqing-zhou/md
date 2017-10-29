#include <mpi.h>
#include <stdio.h>
#include "md.h"

using namespace std;

int main(int argc, char **argv){
  MPI_Init(&argc,&argv);
  MD *md = new MD(argc,argv,MPI_COMM_WORLD);
  delete md;
  MPI_Finalize();
  return 0;
}

