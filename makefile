all: test usecase
test: test_bst.o
	g++ -std=c++11 -o test test_bst.o
	
test_bst.o: test_graph_example.cpp graph.h graph.cpp
	g++ -std=c++11 -c test_graph_example.cpp

usecase: main.o
	g++ -std=c++11 -Wall -g -o usecase main.o

main.o: graph.cpp graph.h usecase.cpp main.cpp	
	g++ -std=c++11 -c -g -Wall main.cpp
