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
        Vertex* parent; 
        int distance;
        int d_time;
        int f_time;
        friend class Graph<Data, Key>;
        
    public:
        Data data; 
        Key key;

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
        vector<vector<Key>> edges;


    public:
        Graph();
        Graph(vector<Key> keys, vector<Data> data, vector<vector<Key>> edges);
        ~Graph();
        Vertex<Data, Key>* get(Key k) const;
        bool reachable(Vertex<Data,Key>* u, Vertex<Data,Key>* v) const;
        void bfs(Vertex<Data,Key> source) const;
        void dfs(Vertex<Data,Key> source) const;
        string print_path(Key u, Key v) const;
        string edge_class(Vertex<Data,Key> u, Vertex<Data,Key> v) const;
        string bfs_tree(Key s) const;
};

#endif 
