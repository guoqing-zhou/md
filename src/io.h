#ifndef IO_H
#define IO_H

#include <mpi.h>
#include <stdio.h>
#include "control.h"
#include "md.h"


using namespace std;

class IO {
  public:
    IO(class MD *,  int, char **, MPI_Comm);
    ~IO();
    void init(class MD *, MPI_Comm);
    void read();
    void write();

  private:
    char *infile;
    int my_rank;
    int num_proc;
    FILE *fp;
    void parse(class MD *md, char *);
    int string_narg(char *);
    
};

#endif
