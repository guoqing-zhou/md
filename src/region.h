#ifndef REGION_H
#define REGION_H

#include <stdio.h>
#include "control.h"

class Region {
public:
  char *shape;
  FLOAT *parameters;
  Region(int, char **);
  bool isin(FLOAT, FLOAT, FLOAT); //check whether is in the region
};

#endif