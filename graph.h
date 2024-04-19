//-----------------------------------------------//
//              Binary Search Tree               //
//               Constructor File                //
//                                               //
// Ethan Tecson, Nhien Hong, Liam Qiunlan        //
//-----------------------------------------------//


#ifndef GRAPH_H
#define GRAPH_H


#include <iostream>
#include <vector>
#include <string>
using namespace std;


template <typename Data, typename Key>
class Graph;


template <typename Data, typename Key>
class Vertex {
   private:
       bool color_white;
       Vertex<Data, Key>* parent;
       vector<Vertex<Data, Key>*> adjacencies_list;
       friend class Graph<Data, Key>;
      
   public:
       Data data;
       Key key;
       int distance;


       Vertex();
       Vertex(Data d, Key k);
       ~Vertex();
       // May need heper function for deleting nodes
};


template <typename Data, typename Key>
class Graph {
   private:
       vector<Vertex<Data,Key>*> vertices;
       vector<vector<Vertex<Data, Key>*>> adjacencies;


   public:
       Graph();
       Graph(vector<Key> keys, vector<Data> data, vector<vector<Key>> edges);
       ~Graph();
       Vertex<Data, Key>* get(Key k) const;
       bool reachable(Key u, Key v) const;
       void bfs(Key source) const;
       void print_path(Key u, Key v) const;
       string edge_class(Vertex<Data,Key> u, Vertex<Data,Key> v) const;
       string bfs_tree(Key s) const;
};


#endif



