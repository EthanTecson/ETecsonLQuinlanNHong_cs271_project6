#include "graph.h"
#include <sstream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>

using namespace std;

//===================================
// Vertex Class
//===================================


/*
 * @brief Empty Constructor for Vertex Class
 *
 * Creates a Vertex Object with no values for key or data
 *
 * @param none
 *
 * @note Pre-Condition: none
 * @note Post-Condition: Creates a Node object
 *
 * @returns none
*/

template <typename Data, typename Key>
Vertex<Data,Key>::Vertex(){
    parent = nullptr;
    color_white = true;
    distance = -1;
}

/**
 * @brief Constructor with values for Vertex Class
 *
 * Creates a Vertex Object with the data and key attributes equal 
 * to the data and key given in the argument
 *
 * @param d - data for vertex object to be initiated with
 * @param k - key for vertex object to be initiated with
 *s
 * @note Pre-Condition: none
 * @note Post-Condition: Creates a Vertex object 
 *
 * @returns none
 */
template <typename Data, typename Key>
Vertex<Data,Key>::Vertex(Data d, Key k){
    parent = nullptr;
    color_white = true;
    distance = -1;
    data = d;
    key = k;
}

/**
 * @brief Deconstructor for Vertex Class
 *
 * Deallocates memory created for vertex objects
 *
 *@param none
 * 
 * @note Pre-Condition: none
 * @note Post-Condition:a All vertex objects deallocated
 *
 * @returns none
 */
template <typename Data, typename Key>
Vertex<Data, Key>::~Vertex() {
    // Nothing needed
    // Will probably need to have a heper function that deletes nodes that 
    // will be used in the Graph deconstructor
}

//===================================
// Graph Class
//===================================

/**
 * @brief Parameter Constructor for Graph Class
 *
 * Creates graph object with parameter keys, data, and adjacencies
 *
 * @param keys vector, data vector, adjacencies vector of vectors
 * 
 * @note Pre-Condition: none
 * @note Post-Condition: creates a Graph object
 *
 * @returns none
 */
template <typename Data, typename Key>
Graph<Data, Key>::Graph(vector<Key> keys, vector<Data> data, vector<vector<Key>> edges) {
    int len = keys.size();
    adjacencies.resize(len);
    
    for( int i = 0; i < len; i++ ) {
        Vertex<Data, Key> *new_vertex = new Vertex<Data, Key>(data[i], keys[i]);
        vertices.push_back(new_vertex);
    }

    for( int j = 0; j < len; j++ ) {
        int edges_len = edges[j].size();
        for( int k = 0; k < edges_len; k++) {
            Vertex<Data, Key> *new_ptr = get(edges[j][k]);
            adjacencies[j].push_back(new_ptr);
        }
    }
}


/**
 * @brief get 
 *
 * returns the pointer to the vertex with key k
 *
 * @param key k
 * 
 * @note Pre-Condition: Graph is a valid graph object
 * @note Post-Condition: no changes, but returns a pointer to the vertex with key k
 *
 * @returns none
 */
template <typename Data, typename Key>
//typename Graph<Data, Key>::Vertex* Graph<Data, Key>::get(Key k) const{
Vertex<Data, Key>* Graph<Data, Key>::get(Key k) const {
    int len = vertices.size();
    //Vertex<Data, Key> *ret = nullptr;

    for( int i = 0; i < len; i++ ) {
        if ( vertices[i]->key == k )
            return vertices[i];
    }

    return nullptr;
}
