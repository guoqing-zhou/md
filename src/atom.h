#include <mpi.h>
#include <stdio.h>

#ifndef ATOM_H
#define ATOM_H
using namespace std;

#define FLOAT float
#define FORMAT_F f
//used in sscanf scanf to read double/float data

class Atom {
  public:
    FLOAT **x, **v, **f;
    FLOAT xlo, xhi, ylo, yhi, zlo, zhi;
    int box_flag;
    
    Atom(class MD *, MPI_Comm);
    ~Atom();
    void box_init(int, char **);

  
};



#endif