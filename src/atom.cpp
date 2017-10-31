#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include "atom.h"



using namespace std;
Atom::Atom(class MD *md, MPI_Comm communicator) {
  box_flag=0;
  types=0;
}

Atom::~Atom(){
  
}

void Atom::atom_init(int narg, char **arg){
  int i;
  if (narg<1) {
    printf("ERROR: atom init\n");
    exit(1);
  }
  sscanf(arg[0], "%d", &types);
  mass = (FLOAT *) malloc(sizeof(FLOAT)*types);
  if (narg==(types+1)){
    for (i=1; i<=types; i++){
      sscanf(arg[i],"%FORMAT_F", &mass[i-1]);
    }
    box_flag=1;
  }
  else {
    printf("ERROR: atom init\n");
    exit(1);
  }
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
  else {
    printf("ERROR: box\n");
    exit(1);
  }
  
}

void Atom::add_region(int narg, char **arg){
  if (narg>0){
    if (regions.count(arg[0])>0){
      printf("ERROR: add region, region exists\n");
      exit(1);
    }
    regions[arg[0]] = new Region(narg-1, arg+1);
  }
  else {
    printf("ERROR: add region\n");
    exit(1);
  }
}

void Atom::create(int narg, char **arg){
  
}