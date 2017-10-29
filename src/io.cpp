#include <mpi.h>
#include <stdio.h>
#include "io.h"

IO::IO(class MD *, char *infile="md.in"){
  
}

IO::~IO(){
  
}

void IO::init(){
  printf("IO::init()\n");
}
