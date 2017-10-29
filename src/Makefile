#makefile for this project
md: main.o md.o io.o
	mpic++ -o md *.o

main.o: main.cpp
	mpic++ -c main.cpp

io.o: io.h io.cpp
	mpic++ -c io.h io.cpp

md.o: md.h md.cpp
	mpic++ -c md.h md.cpp

clean:
	rm md *.o