#ifndef MD_H
#define MD_H

#include <mpi.h>
#include <stdio.h>
#include "io.h"
#include "atom.h"
#include "control.h"

using namespace std;


class MD {
 public:
                                 
  class IO *io;                    // input script processing
  class Atom *atom;              // atom-based quantities
  //class Update *update;          // integrators/minimizers
  //class Neighbor *neighbor;      // neighbor lists
  //class Comm *comm;              // inter-processor communication
  //class Force *force;            // inter-particle forces
  //class Output *output;          // thermo/dump/restart
  //class Timer *timer;            // CPU timing info

  MPI_Comm world;                // MPI communicator
  
  MD(int, char **, MPI_Comm);
  ~MD();
  void procs(int, char **);
  
  int my_rank, proc_flag;
  int pnx, pny, pnz; //processors in each direction
  int num_proc;
  int proc_pos[3], proc_neigh[6]; 
  //this proc postion
  //six neighbors of current proc
  
private:
  int proc_rank(int, int, int);
/*
  void create();
  void post_create();
  void init();
  void destroy();

 private:
  md() {};                   // prohibit using the default constructor
  md(const md &) {};     // prohibit using the copy constructor
*/
};

#endif