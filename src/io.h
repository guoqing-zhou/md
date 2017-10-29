#include <mpi.h>
#include <stdio.h>

#ifndef IO_H
#define IO_H

class IO {
  public:
    IO(class MD *, char *);
    ~IO();
    void init(); //create an empty 
    void restart();
    void write_restart();
  
  private:
    int write_flag; //flag to decide whether write the state when delete the class
};

#endif