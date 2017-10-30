#include <mpi.h>
#include <stdio.h>
#include "io.h"
#include "atom.h"

using namespace std;

#ifndef MD_H
#define MD_H

class MD {
 public:
                                 
  class IO *io;                    // input script processing
  class Atom *atom;              // atom-based quantities
  //class Update *update;          // integrators/minimizers
  //class Neighbor *neighbor;      // neighbor lists
  //class Comm *comm;              // inter-processor communication
  //class Domain *domain;          // simulation box
  //class Force *force;            // inter-particle forces
  //class Output *output;          // thermo/dump/restart
  //class Timer *timer;            // CPU timing info

  MPI_Comm world;                // MPI communicator
  
  MD(int, char **, MPI_Comm);
  ~MD();
  int test;
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