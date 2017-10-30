#!/bin/sh
make clean
make
#mpirun -np 2 ./md md.in
./md md.in
