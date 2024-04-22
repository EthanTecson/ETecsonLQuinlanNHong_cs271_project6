all: test 
test: test_graph.o
	g++ -std=c++11 -o test test_graph.o
	
test_graph.o: test_graph.cpp graph.h graph.cpp
	g++ -std=c++11 -c test_graph.cpp

