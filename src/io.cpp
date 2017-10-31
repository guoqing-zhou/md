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

}

IO::~IO(){

}

void IO::parse(class MD *md, char *line){
 
  char **arg=NULL;
  int narg, n;
  char *pch;
  //split each line in the input file
  narg=string_narg(line);
  if (narg==0) return;
  
  arg = (char **)malloc(sizeof(char *)*narg);
  pch = strtok(line, " ");
  arg[0] = pch;
  for (n=1; n<narg; n++){
    pch = strtok (NULL, " ");
    arg[n] = pch;
  }
  
  if(strcmp(arg[0],"box")==0){
    md->atom->box_init(narg-1, arg+1);
  }
  else if (strcmp(arg[0],"procs")==0){
    md->procs(narg-1, arg+1);
  }
  else if (strcmp(arg[0],"atom")==0){
    md->atom->atom_init(narg-1, arg+1);
  }
  else if (strcmp(arg[0],"region")==0){
    md->atom->add_region(md, narg-1, arg+1);
    /*
#ifdef DEBUG
    if (md->atom->regions[arg[1]]->isin(11.0, 5.0, 5.0)){
      printf("Atom (%f %f %f) in the region %s\n", 5.0, 5.0, 5.0, arg[1]);
    }
    else{
      printf("Atom (%f %f %f) not in the region %s\n", 11.0, 5.0, 5.0, arg[1]);
    }
#endif
    */
  }
  /*
  else if (strcmp(arg[0],"create")==0){
    md->atom->create(narg-1, arg+1);
  }
  */
  if (arg != NULL) free(arg);
}

//count how many substrings in the string
//and replace '\n' with '\0', '\t' with ' '
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
  
  
  




