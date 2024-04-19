#include "graph.h"
#include <sstream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>

using namespace std;


static int time_var;

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
   adjacencies.resize(len);
  
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
Vertex<Data, Key>* Graph<Data, Key>::get(Key k) const {
   int len = vertices.size();


   for( int i = 0; i < len; i++ ) {
       if ( vertices[i]->key == k )
           return vertices[i];
   }


   return nullptr;
}

/**
* @brief reachable
*
* Determines whether or not the vertex with key "v" is reachable 
* from the vertex of key "u"
*
* @param u - the key of the starting node of reachability
* @param v - the key of the node to be checked if reachable from u 
*
* @note Pre-Condition: Graph is a valid graph object with valid Vertex objects
* @note Post-Condition: none
*
* @returns True or False depending on if v is reachable from u
*/
template <typename Data, typename Key>
bool Graph<Data,Key>::reachable(Key u, Key v) const{

    // Check if vertex keys are in graph
    int check_counter = 0;
    for ( int i = 0; i < vertices.size(); i++ ){
        if (vertices[i]->key == u){
            check_counter++;
        }
        if (vertices[i]->key == v){
            check_counter++;
        }
    }

    if ( check_counter != 2 ){
        return false;
    }

    // Give all nodes reachable from u a distance
    bfs(u);

    // Get node that will be checked if reachable
    Vertex<Data, Key> *v_ptr = get(v);

    // If node to be reached has no set distance, it is not reachable from u
    if ( v_ptr->distance == -1 ){
        return false;
    }

    return true;

}


// Function is not finished at time of push

// template<typename Data, typename Key>
// string Graph<Data, Key>::print_path(Key u, Key v) const{

//     // Check if vertex keys are in graph
//     int check_counter = 0;
//     for ( int i = 0; i < vertices.size(); i++ ){
//         if (vertices[i]->key == u){
//             check_counter++;
//         }
//         if (vertices[i]->key == v){
//             check_counter++;
//         }
//     }

//     stringstream ss;

//     Vertex<Data,Key>* u_ptr = get(u);
//     Vertex<Data,Key>* v_ptr = get(v);

//     if (u == v){
//         ss << 
//     }
// }



/**
* @brief bfs
*
* performs a breadth-first search on the graph, starting at source s
*
* @param source s, of type Key
*
* @note Pre-Condition: source is the key of a valid Vertex<Data,Key> object
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


/**
* @brief dfs
*
* performs a depth-first search on the graph, starting at source s
*
* @param source s, of type Key
*
* @note Pre-Condition: graph is a valid graph
* @note Post-Condition: performs dfs on graph
*
* @returns none, but changes the attributes of the vertices
*/
// template <typename Data, typename Key>
// void Graph<Data, Key>::dfs() const {
//     int len = vertices.size();
//     for( int i = 0; i < len; i++ ) {
//         vertices[i]->color = 0;
//         vertices[i]->parent = nullptr;
//     }

//     time_var = 0;

//     for( int j = 0; j < len; j++ ) {
//         if( vertices[j]->color == 0 )
//             dfs_visit( vertices[j] );
//     }
// }


/**
* @brief dfs-visit
*
* helper function for dfs
*
* @param Vertex u
*
* @note Pre-Condition: graph is a valid graph
* @note Post-Condition: 
*
* @returns none, but changes the attributes of the vertices
*/
template <typename Data, typename Key>
void Graph<Data, Key>::dfs_visit( Vertex<Data,Key> *u ) const {
    time_var = time_var + 1;
    u->discovered = time_var;
    u->color = 1;
    int len = u->adjacencies_list.size();
    
    for( int i = 0; i < len; i++ ) {
        if( u->adjacencies_list[i]->color == 0) {
            u->adjacencies_list[i]->parent = u;
            dfs_visit( u->adjacencies_list[i] );
        }
    }

    u->color = 1;
    time_var = time_var + 1;
    u->finished = time_var;
}






/**
* @brief edge_class
*
* 
*
* @param 
*
* @note Pre-Condition: 
* @note Post-Condition: 
*
* @returns 
*/
template <typename Data, typename Key>
string Graph<Data, Key>::edge_class(Key u_key, Key v_key) const {
    Vertex<Data,Key> *u = get( u_key );
    Vertex<Data,Key> *v = get( v_key );

    int len = vertices.size();
    string ret = "no edge";

    for( int i = 0; i < len; i++ ) {
        vertices[i]->color = 0;
        vertices[i]->parent = nullptr;
    }

    time_var = 0;

    for( int j = 0; j < len; j++ ) {
        if( vertices[j]->color == 0 && vertices[j] == u ) {
            ret = edge_class_helper( u, v, ret );
        }
        else if( vertices[j]->color == 0 ) {
            dfs_visit( vertices[j] );
        }
    }

    return ret;
}


/**
* @brief edge_class_helper
*
* helper function for edge_class
*
* @param Vertex u
*
* @note Pre-Condition: graph is a valid graph
* @note Post-Condition: 
*
* @returns none, but changes the attributes of the vertices
*/
template <typename Data, typename Key>
string Graph<Data, Key>::edge_class_helper( Vertex<Data,Key> *u, Vertex<Data,Key> *v, string ret ) const {
    time_var = time_var + 1;
    u->discovered = time_var;
    u->color = 1;
    int len = u->adjacencies_list.size();
    
    for( int i = 0; i < len; i++ ) {
        if( u->adjacencies_list[i]->color == 1 )
            return "back edge";
        else if( u->adjacencies_list[i]->color == 2 ){
            if( u->distance > u->adjacencies_list[i]->distance )
                return "forward edge";
            else 
                return "cross edge";
        }
        else if( u->adjacencies_list[i]->color == 0 && u->adjacencies_list[i] == v ) {
            return "tree edge";
        }
        else if ( u->adjacencies_list[i]->color == 0 ) {
            u->adjacencies_list[i]->parent = u;
            dfs_visit( u->adjacencies_list[i] );
        }
    }

    u->color = 1;
    time_var = time_var + 1;
    u->finished = time_var;

    return ret;
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
 