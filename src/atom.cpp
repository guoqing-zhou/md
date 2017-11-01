#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include "atom.h"



using namespace std;
Atom::Atom(class MD *md, MPI_Comm communicator) {
  box_flag=0;
  types=0;
  atom_flag=0;//check whether allocate memory for the atom info arrays
}

Atom::~Atom(){
  if(atom_flag){
    free(x);
    free(v);
    free(f);
    free(id);
  }
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
    printf("ERROR: Atom::atom_init()\n");
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
    if(box[0]>box[1] || box[2]>=box[3] || box[4]>=box[5]){
      printf("ERROR: Atom::box_init(), box boundary error\n");
      exit(1);
    }
  }
  else {
    printf("ERROR: Atom::box_init()\n");
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
    printf("ERROR: Atom::add_region()\n");
    exit(1);
  }
}

void Atom::create(int narg, char **arg){
  /*
  FLOAT M[9]={3.0, 2.0, 4.0,3.0,2.0,5.0,9.0,1.0,4.0};
  FLOAT InvM[9];
  int i, j;
  invert_matrix(M, InvM);
  for (i=0; i<3; i++){
    for (j=0; j<3; j++){
      printf("%f ", InvM[3*i+j]);
    }
    printf("\n");
  }
  */
  //create type region percent seed origin (three basis vectors)
  FLOAT origin[3], percent, basis[9], Inv[9];
  int type, region, seed, i, ib[3][2];
  if (narg==16){
    sscanf(arg[0], "%d", &type);
    if(strcmp(arg[1], "box")==0) region=0;
    else sscanf(arg[1], "%d", &region);
    sscanf(arg[2], "%FORMAT_F", &percent);
    sscanf(arg[3], "%d", &seed);
    for (i=0; i<3; i++){
      sscanf(arg[4+i], "%FORMAT_F", &origin[i]);
      sscanf(arg[7+i], "%FORMAT_F", &basis[i]);
      sscanf(arg[10+i], "%FORMAT_F", &basis[3+i]);
      sscanf(arg[13+i], "%FORMAT_F", &basis[6+i]);
    }
    invert_matrix(basis, Inv);

  }
  else{
    printf("ERROR: Atom::create()\n");
    exit(1);
  }



}

void Atom::set_max(int narg, char **arg){
  int N;
  if (narg==1){
    sscanf(arg[0], "%d", &N);
    allocate_memory(N);
  }
  else{
    printf("ERROR: Atom::set_max()\n");
    exit(1);
  }
}

void Atom::allocate_memory(int N=MAX_NUM_ATOM){
  x = (FLOAT *)malloc(sizeof(FLOAT)*N*3);
  v = (FLOAT *)malloc(sizeof(FLOAT)*N*3);
  f = (FLOAT *)malloc(sizeof(FLOAT)*N*3);
  id = (long long *)malloc(sizeof(long long)*N);
  if (x==NULL || v==NULL || f==NULL){
    printf("ERROR: Atom::allocate_memory()\n");
    exit(1);
  }
  else{
    atom_flag=1;
  }
}

inline void Atom::invert_matrix(FLOAT *A, FLOAT *InvA){
  //M and InvM are 3*3 matrix
  FLOAT det, M[3][3], InvM[3][3];
  int i, j;
  for (i=0; i<3; i++){
    for (j=0; j<3; j++){
      M[i][j]=A[i*3+j];
    }
  }
  det=M[0][0]*M[1][1]*M[2][2]+M[0][1]*M[1][2]*M[2][0]+M[0][2]*M[1][0]*M[2][1];
  det-=(M[0][2]*M[1][1]*M[2][0]+M[0][1]*M[1][0]*M[2][2]+M[0][0]*M[1][2]*M[2][1]);
  if (det==0.0){
    printf("ERROR: Atom::invert_matrix(), basis vectors matrix det 0\n");
    exit(1);
  }
  InvM[0][0]=(M[1][1]*M[2][2]-M[1][2]*M[2][1])/det;
  InvM[0][1]=(M[0][2]*M[2][1]-M[0][1]*M[2][2])/det;
  InvM[0][2]=(M[0][1]*M[1][2]-M[0][2]*M[1][1])/det;
  InvM[1][0]=(M[1][2]*M[2][0]-M[1][0]*M[2][2])/det;
  InvM[1][1]=(M[0][0]*M[2][2]-M[0][2]*M[2][0])/det;
  InvM[1][2]=(M[0][2]*M[1][0]-M[0][0]*M[1][2])/det;
  InvM[2][0]=(M[1][0]*M[2][1]-M[1][1]*M[2][0])/det;
  InvM[2][1]=(M[0][1]*M[2][0]-M[0][0]*M[2][1])/det;
  InvM[2][2]=(M[0][0]*M[1][1]-M[0][1]*M[1][0])/det;

  for (i=0; i<3; i++){
    for (j=0; j<3; j++){
      InvA[i*3+j]=InvM[i][j];
    }
  }

}
