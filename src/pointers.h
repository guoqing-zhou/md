#ifndef POINTERS_H
#define POINTERS_H

#include <mpi.h>
#include "md.h"
using namespace std;

class Pointers {
 public:
  Pointers(MD *ptr) :
    md(ptr),
    io(ptr->io),
    atom(ptr->atom) {}
  virtual ~Pointers() {}

 protected:
  MD *md;
  Atom *&atom;
  IO *&io;
  
};


#endif