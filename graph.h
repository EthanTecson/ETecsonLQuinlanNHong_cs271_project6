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
        Data data; 
        Key key;
        vector<Vertex<Data, Key>*> edges;
        friend class Graph<Data, Key>;
        bool color_white;
        Vertex* parent; 
    public:
        Vertex();
        Vertex(Data d, Key k);
        ~Vertex();
        // May need heper function for deleting nodes
};

template <typename Data, typename Key>
class Graph {
    private:
        Vertex<Data, Key>* source;
    public:
        Graph();
        Graph(vector<Key> keys, vector<Data> data, vector<vector<Key>> edges);
        ~Graph();
        Vertex<Data, Key>* get(Key k) const;
        bool reachable(Vertex<Data,Key>* u, Vertex<Data,Key>* v) const;
        Node<Data, Key>* bfs(Vertex<Data,Key> source) const;
        string print_path(Key u, Key v) const;
        string edge_class(Vertex<Data,Key> u, Vertex<Data,Key> v) const;
        string bfs_tree(Key s) const;
};

#endif 
