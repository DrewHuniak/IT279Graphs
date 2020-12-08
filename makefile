all:Graph.o TextMenu.o graphRunner.o DisjointSet.o
	g++ Graph.o TextMenu.o graphRunner.o DisjointSet.o -o out
Graph.o:Graph.cpp
	g++ -c Graph.cpp
TextMenu.o:TextMenu.cpp
	g++ -c TextMenu.cpp
graphRunner.o:graphRunner.cpp
	g++ -c graphRunner.cpp
DisjointSet.o:DisjointSet.cpp
	g++ -c DisjointSet.cpp
clean:
	rm *.o out