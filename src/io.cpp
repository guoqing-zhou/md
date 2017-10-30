#include <mpi.h>
#include <stdio.h>
#include "io.h"
#include <string.h>

#define DEBUG  

using namespace std;

IO::IO(class MD *md, int narg, char **arg, MPI_Comm communicator) : Pointers(md) {
  char buff[300];
  MPI_Comm_rank(communicator, &my_rank);
  MPI_Comm_size(communicator, &num_proc);
  if (narg<2) exit(1);
  infile=arg[1];

  fp=fopen(infile, "r");
  while((fgets(buff, 250, fp)) != NULL){
    parse(md, buff);
  }
    
  fclose(fp);
  //MPI_Bcast(filename, filename_length*sizeof(char), MPI_CHAR, 0, communicator);
  //MPI_Bcast(file_flag, command_length*sizeof(char), MPI_CHAR, 0, communicator);
  //MPI_Barrier(communicator);  
}

IO::~IO(){

}

void IO::parse(class MD *md, char *line){
  char **arg;
  int narg;
  string_split(line, &narg, arg);
  if (strcmp(arg[0],"create")==0){
    
  }
  else if(strcmp(arg[0],"box")==0){
    md->atom->box_init(narg-1, arg+1);
  }
  //printf("box: %f %f\n", atom->xlo, atom->xhi);
  
}

void IO::string_split(char *str, int *narg, char **arg){
  int n=0;
  char *pch;
  if (str[0]=='#') return;
  pch = strtok(str, " ");
  n++;
  while (pch != NULL){
    //printf ("%s\n",pch);
    pch = strtok (NULL, " ");
    n++;
  }
  arg = (char **)malloc(sizeof(char *)*n);
  *narg = n;
  
  pch = strtok(str, " ");
  *(arg+n) = pch;
  n++;
  while (*(arg+n-1) != NULL){
    //printf ("%s\n",*(arg+n-1));
    pch = strtok (NULL, " ");
    *(arg+n) = pch;
    n++;
  }
}
  
  
  



void IO::init(){
  
}
