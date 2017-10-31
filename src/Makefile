#makefile for this project
md: main.o md.o io.o atom.o region.o
	mpic++ -o md *.o

main.o: main.cpp 
	mpic++ -c main.cpp

io.o: io.h io.cpp control.h
	mpic++ -c io.cpp
	
atom.o: atom.h atom.cpp control.h
	mpic++ -c atom.cpp

md.o: md.h md.cpp control.h
	mpic++ -c md.cpp

region.o: region.h region.cpp control.h
	mpic++ -c region.cpp	
		
clean:
	rm md *.o