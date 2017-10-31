#include <stdio.h>
#include <string.h>
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

void Region::min_rect(FLOAT *para){
  int i;
  if (strcmp(shape, "rect")==0){
    for (i=0; i<6; i++)
      para[i]=parameters[i];
  }
  else {
    printf("ERROR: Region::min_rect()\n");
    exit(1);
  }
  
}

void Region::check(FLOAT *box){
  FLOAT MinRect[6];
  min_rect(MinRect);
  if (MinRect[0]<box[0] || MinRect[1]>box[1] || MinRect[2]<box[2] || MinRect[3]>box[3] || MinRect[4]<box[4] || MinRect[5]>box[5]){
    printf("region is out of the box\n");
    exit(1);
  }
}



