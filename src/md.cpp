#include <mpi.h>
#include <stdio.h>
#include "md.h"

using namespace std;

MD::MD(int, char **, MPI_Comm){
  input = new Input();
  input->test();
}

MD::~MD(){
  delete input;
}