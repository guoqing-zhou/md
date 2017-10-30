#include <mpi.h>
#include <stdio.h>
#include "pointers.h"

#ifndef IO_H
#define IO_H

#define filename_length 100
#define command_length 20

using namespace std;

class IO : protected Pointers {
  public:
    IO(class MD *, int, char **, MPI_Comm);
    ~IO();
    void init(); //create an empty
    void restart();
    void write_restart();

  private:
    char *infile;
    char command[command_length]; //flag to decide whether write the state when delete the class
    int my_rank;
    int num_proc;
    char filename[filename_length], myfilename[filename_length];
    FILE *fp;
    void parse(class MD *md, char *);
    void string_split(char *, int *, char **);
    
    
};

#endif
