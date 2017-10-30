#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include "atom.h"


using namespace std;
Atom::Atom(class MD *md, MPI_Comm communicator) : Pointers(md) {
  box_flag=0;
  
}

Atom::~Atom(){
  
}

void Atom::box_init(int narg, char **arg){
  if (strcmp(arg[0], "rect")==0 && narg==7){
    sscanf(arg[1],"%FORMAT_F", &xlo);
    sscanf(arg[2],"%FORMAT_F", &xhi);
    sscanf(arg[3],"%FORMAT_F", &ylo);
    sscanf(arg[4],"%FORMAT_F", &yhi);
    sscanf(arg[5],"%FORMAT_F", &zlo);
    sscanf(arg[6],"%FORMAT_F", &zhi);
    box_flag=1;
  }
  
}