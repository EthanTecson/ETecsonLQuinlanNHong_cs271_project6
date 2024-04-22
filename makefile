all: test 
test: test_bst.o
	g++ -std=c++11 -o test test_bst.o
	
test_bst.o: test_graph_example.cpp graph.h graph.cpp
	g++ -std=c++11 -c test_graph_example.cpp

