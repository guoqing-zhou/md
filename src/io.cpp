#include <mpi.h>
#include <stdio.h>
#include "io.h"

IO::IO(class MD *md, const char *infile){
  printf("File name %s\n", infile);
}

IO::IO(class MD *md){
  IO(md, "md.in");
}


IO::~IO(){

}

void IO::init(){
  printf("IO::init()\n");
}
