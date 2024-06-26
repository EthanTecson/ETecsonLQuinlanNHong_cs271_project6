
//-----------------------------------------------//
//                    Graph                      //
//                 Header File                   //
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
       
       int color; // 0 = white, 1 = gray, 2 = black
       int discovered;
       int finished;
      
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

   public:
       Graph();
       Graph(vector<Key> keys, vector<Data> data, vector<vector<Key>> edges);
       ~Graph();
       Vertex<Data, Key>* get(Key k) const;
       bool reachable(Key u, Key v) const;
       void bfs(Key source) const;
       void print_path(Key u, Key v) const;
       void bfs_tree(Key s) const;
       void dfs_visit( Vertex<Data,Key> *u ) const; 
       string edge_class(Key u_key, Key v_key) const;
       string edge_class_helper( Vertex<Data,Key> *u, Vertex<Data,Key> *v, string ret ) const;
};

#endif

