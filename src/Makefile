#makefile for this project
md: main.o md.o io.o atom.o
	mpic++ -o md *.o

main.o: main.cpp
	mpic++ -c main.cpp

io.o: io.h io.cpp 
	mpic++ -c io.cpp
	
atom.o: atom.h atom.cpp 
	mpic++ -c atom.cpp

md.o: md.h md.cpp
	mpic++ -c md.cpp
	
		
clean:
	rm md *.o