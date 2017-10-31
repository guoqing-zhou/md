#include <stdio.h>
#include <string>
#include "region.h"

Region::Region(int narg, char **arg){
  int i;
  if (narg>0){
    if(strcmp(arg[0], "rect")==0 && narg==7){//rect xlo xhi ylo yhi zlo zhi
      parameters=(FLOAT *)malloc(sizeof(FLOAT)*6);
      shape=arg[0];
      for (i=1; i<=6; i++){
        sscanf(arg[i], "%FORMAT_F", &parameters[i-1]);
      }
    }
  }
  else {
    printf("ERROR: Region\n");
    exit(1);
  }
  
}

bool Region::isin(FLOAT x, FLOAT y, FLOAT z){
  if (strcmp(shape, "rect")==0){
    return ( (x>=parameters[0]) && (x<=parameters[1]) && 
      (y>=parameters[2]) && (y<=parameters[3]) && 
      (z>=parameters[4]) && (z<=parameters[5]));
  }
  else {
    printf("ERROR: Region::isin()\n");
    exit(1);
  }
}