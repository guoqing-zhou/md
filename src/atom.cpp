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
    sscanf(arg[1],"%FORMAT_F", &box[0]);
    sscanf(arg[2],"%FORMAT_F", &box[1]);
    sscanf(arg[3],"%FORMAT_F", &box[2]);
    sscanf(arg[4],"%FORMAT_F", &box[3]);
    sscanf(arg[5],"%FORMAT_F", &box[4]);
    sscanf(arg[6],"%FORMAT_F", &box[5]);
    box_flag=1;
  }
  else {
    printf("ERROR: box\n");
    exit(1);
  }
  
}

void Atom::add_region(class MD *md, int narg, char **arg){
  int ID;
  if (narg>0){
    sscanf(arg[0], "%d", &ID);
    if (regions.count(ID)==1){
      printf("ERROR: add region, region exists\n");
      exit(1);
    }
    
    regions[ID] = new Region(narg-1, arg+1);
    
    regions[ID]->check(box);  
    //printf("%f %f\n", box[0], box[1]);
    //printf("%f %f\n", regions[arg[0]]->parameters[0], regions[arg[0]]->parameters[1]); 
  }
  else {
    printf("ERROR: add region\n");
    exit(1);
  }
}

void Atom::create(int narg, char **arg){
  
}