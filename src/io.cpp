#include <mpi.h>
#include <stdio.h>
#include "io.h"

IO::IO(class MD *md, char *infile){
  
}

IO::IO(class MD *md){
  IO(md, "md.in");
}


IO::~IO(){
  
}

void IO::init(){
  printf("IO::init()\n");
}
