#include "graph.h"
#include <sstream>
#include <string>
#include <queue>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;


//===================================
// Vertex Class
//===================================




/**
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
   adjacencies_list = vector<Vertex<Data,Key>*>();
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
   adjacencies_list = vector<Vertex<Data,Key>*>();
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
   adjacencies_list.resize(len);
  
   // Load graph->vertices with new vertexes
   for( int i = 0; i < len; i++ ) {
       Vertex<Data, Key> *new_vertex = new Vertex<Data, Key>(data[i], keys[i]);
       vertices.push_back(new_vertex);
   }


   // Vertex adjacencies_list
   for ( int i = 0; i < edges.size(); i++ ){
       Vertex<Data,Key>* current_vertex = get(keys[i]);
       for ( int j = 0; j < edges[i].size(); j++){
           current_vertex->adjacencies_list.push_back(get(edges[i][j]));
       }
   }


   // Adjacencies
   for( int j = 0; j < len; j++ ) {
       int edges_len = edges[j].size();
       for( int k = 0; k < edges_len; k++) {
           Vertex<Data, Key> *new_ptr = get(edges[j][k]);
           adjacencies_list[j].push_back(new_ptr);
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
Vertex<Data, Key>* Graph<Data, Key>::get(Key k) const {
   int len = vertices.size();


   for( int i = 0; i < len; i++ ) {
       if ( vertices[i]->key == k )
           return vertices[i];
   }


   return nullptr;
}


/**
* @brief bfs
*
* performs a breadth-first search on the graph, starting at source s
*
* @param source s, of type Key
*
* @note Pre-Condition: none
* @note Post-Condition: performs a bfs on the graph
*
* @returns none, but changes the attributes of the vertices
*/


template <typename Data, typename Key>
void Graph<Data, Key>::bfs(Key source) const {


   int len = vertices.size();
   for( int i = 0; i < len; i++ ) {
       vertices[i]->color_white = true;
       vertices[i]->distance = -1;
       vertices[i]->parent = nullptr;
   }


   Vertex<Data, Key> *s = get(source);
   s->color_white = false;
   s->distance = 0;
   s->parent = nullptr;


   queue<Vertex<Data, Key>*> Q;
   Q.push(s);


   while( !Q.empty() ) {
       Vertex<Data, Key> *u = Q.front();
       Q.pop();


       int adj_len = u->adjacencies_list.size();


       vector<Vertex<Data, Key>*> *adj_list_ptr = &u->adjacencies_list;


       for( int j = 0; j < adj_len; j++ ) {
           if ( (*adj_list_ptr)[j]->color_white ) {
               (*adj_list_ptr)[j]->color_white = false;
               (*adj_list_ptr)[j]->distance = u->distance + 1;
               (*adj_list_ptr)[j]->parent = u;


               Q.push( (*adj_list_ptr)[j] );
           }


           u->color_white = false;
       }
   }
}

template <typename Data, typename Key>
string Graph<Data, Key>::bfs_tree(Key s) const {
    // Check if the starting vertex exists
    if (get(s) == nullptr) {
        return "Source vertex not found";
    }

    // Create a queue for BFS traversal
    deque<Vertex<Data, Key>*> q;

    // Create a set to keep track of visited vertices
    unordered_set<Key> visited;

    // Initialize a stringstream to store the result
    stringstream result;

    // Add the source vertex to the queue and mark it visited
    q.push_back(get(s));
    visited.insert(s);

    // Traverse BFS
    while (!q.empty()) {
        // Get the number of vertices in the current level
        int level_size = q.size();

        // Initialize a stringstream to store vertices in the current level
        stringstream current_level_str;

        // Process all vertices in the current level
        for (int i = 0; i < level_size; i++) {
            // Get the front vertex from the queue
            Vertex<Data, Key>* vertex = q.front();
            q.pop_front();

            // Append the key of the vertex to the current level string
            current_level_str << (current_level_str.tellp() == 0 ? "" : " ") << vertex->key;

            // Visit all adjacent vertices of the current vertex
            for (auto neighbor : vertex->adjacencies_list) {
                // Check if the neighbor vertex has not been visited
                if (visited.count(neighbor->key) == 0) {
                    // Mark the neighbor vertex as visited and add it to the queue
                    q.push_back(neighbor);
                    visited.insert(neighbor->key);
                }
            }
        }

        // Append the current level string to the result
        result << current_level_str.str() << "\n";
    }

    // Convert the stringstream to a string and return
    cout << result.str() << endl;
    return result.str();
}
