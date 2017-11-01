#ifndef ATOM_H
#define ATOM_H

#include <mpi.h>
#include <stdio.h>
#include "control.h"
#include "region.h"
#include <map>
using namespace std;

class Atom {
  public:
    FLOAT *x, *v, *f;
    FLOAT box[6]; //box dimension
    FLOAT *mass;
    FLOAT box_local[6]; //local box dimension
    int Natoms, types, box_flag, atom_flag;
    // numver of atoms in this procs, atom types, flag to check whether box is set
    long long num_atoms, *id; // total number of atoms, id of the atom
    //the type of the atom is also stored in the id
    //as there will be trillion of atom, needs to use long long for id, (64 bits)
    // the top 7 bits are used for types, ignore the sign bit
    // the rest of 56 bits are used for id
    // there is no MPI unsigned long long type

    map<int, class Region *> regions;

    Atom(class MD *, MPI_Comm);
    ~Atom();
    void box_init(int, char **);
    void create(int, char **);
    void atom_init(int, char **);
    void add_region(class MD *, int, char **);
    void set_max(int, char **);

  private:
    void allocate_memory(int);

};



#endif
