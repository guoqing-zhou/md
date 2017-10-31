#include <mpi.h>
#include <stdio.h>
#include "io.h"
#include <string.h>
#define DEBUG
 

using namespace std;

IO::IO(class MD *md, int narg, char **arg, MPI_Comm communicator) {
  MPI_Comm_rank(communicator, &my_rank);
  MPI_Comm_size(communicator, &num_proc);
  if (narg<2) exit(1);
  infile=arg[1];
  
}

void IO::init(class MD *md, MPI_Comm communicator){
  char buff[300];
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
 
  char **arg=NULL;
  int narg, n;
  char *pch;
  //split each line in the input file
  narg=string_narg(line);
  arg = (char **)malloc(sizeof(char *)*narg);
  if (narg>0){
    pch = strtok(line, " ");
    arg[0] = pch;
    for (n=1; n<narg; n++){
      pch = strtok (NULL, " ");
      arg[n] = pch;
    }
  }
  
  if(strcmp(arg[0],"box")==0){
    md->atom->box_init(narg-1, arg+1);
  }
  else if (strcmp(arg[0],"create")==0){
    
  }
  
  free(arg);
}


inline int IO::string_narg(char *line){
  int l=strlen(line);
  int n=0, i;
  if(line[0] == '#') return 0;
  for (i=0; i<l; i++){
    if (line[i]=='\t') line[i]=' ';
    if (line[i]=='\n') line[i]='\0';
  }
  l=strlen(line);
  if (line[0] != ' ') n=1;
  for (i=1; i<l; i++){
    if (line[i-1]==' ' && line[i]!=' ') n++;
  }
  return n;
}
  
  
  




