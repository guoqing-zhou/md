#include <mpi.h>
#include <stdio.h>
#include "md.h"

using namespace std;

MD::MD(int narg, char **arg, MPI_Comm communicator ){
  MPI_Comm_rank(communicator, &my_rank);
  MPI_Comm_size(communicator, &num_proc);
  proc_flag=0;

  atom = new Atom(this, communicator);
  io = new IO(this, narg, arg, communicator);
  
  io->init(this, communicator);
}

MD::~MD(){
  delete io;
  delete atom;
}

void MD::procs(int narg, char **arg){
  if(narg==3){
    sscanf(arg[0], "%d", &pnx);
    sscanf(arg[1], "%d", &pny);
    sscanf(arg[2], "%d", &pnz);
  }
  else{
    printf("ERROR: procs\n");
    exit(1);
  }
  if (num_proc != pnx*pny*pnz){
    printf("ERROR: procs\n");
    exit(1);
  }
  //my_rank:0~num_proc
  //assign in the order of nx, ny, nz
  proc_pos[2] = my_rank/(pnx*pny);
  proc_pos[1] = (my_rank-proc_pos[2]*pnx*pny)/pnx;
  proc_pos[0] = my_rank%(pnx);
  //six neighbor proc's rank
  proc_neigh[0]=proc_rank(proc_pos[0]-1, proc_pos[1], proc_pos[2]);
  proc_neigh[1]=proc_rank(proc_pos[0]+1, proc_pos[1], proc_pos[2]);
  proc_neigh[2]=proc_rank(proc_pos[0], proc_pos[1]-1, proc_pos[2]);
  proc_neigh[3]=proc_rank(proc_pos[0], proc_pos[1]+1, proc_pos[2]);
  proc_neigh[4]=proc_rank(proc_pos[0], proc_pos[1], proc_pos[2]-1);
  proc_neigh[5]=proc_rank(proc_pos[0], proc_pos[1], proc_pos[2]+1);
  //printf("%d: %d %d %d\n", my_rank, proc_pos[0], proc_pos[1], proc_pos[2]);
  //printf("%d: %d %d %d %d %d %d\n", my_rank, proc_neigh[0], proc_neigh[1], proc_neigh[2],
  //                                  proc_neigh[3], proc_neigh[4], proc_neigh[5]);
  proc_flag=1;
  
}

inline int MD::proc_rank(int nx, int ny, int nz){
  return ((nz+pnz)%pnz)*(pnx*pny)+((ny+pny)%pny)*pnx+((nx+pnx)%pnx);
}