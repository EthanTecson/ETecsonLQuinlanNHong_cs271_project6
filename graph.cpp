#include "graph.h"
#include <sstream>
#include <string>
#include <queue>
#include <stack>

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
* @note Post-Condition: Creates a Vertex object
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
   // Will probably need to have a heper function that deletes Vertices that
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
* @param u - the key of the starting vertex of reachability
* @param v - the key of the vertes to be checked if reachable from u 
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

    // Give all vertexes reachable from u a distance other than -1
    bfs(u);

    // Get vertex that will be checked if reachable
    Vertex<Data, Key> *v_ptr = get(v);

    // If vertex to be reached has no set distance, it is not reachable from u
    if ( v_ptr->distance == -1 ){
        return false;
    }

    return true;

}


/**
* @brief print_path
*
* Prints the shortest path between the vertex with key 'u' and key 'v'
*
* @param u - Starting vertex to print path
* @param v - Last vertex to print path
*
* @note Pre-Condition: u and v are of valid Key data types
* @note Post-Condition: none
*
* @returns A string show the shortest path between vertex with key 'u' and key 'v'
*/
template<typename Data, typename Key>
void Graph<Data, Key>::print_path(Key u, Key v) const{

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

    stringstream ss;

    // Need to reference nodes of given keys
    Vertex<Data,Key>* u_ptr = get(u);
    Vertex<Data,Key>* v_ptr = get(v);

    // Get all vertices parents
    bfs(u);

    stack<Vertex<Data,Key>*> vertexStack;

    // Get path
    while (v_ptr != nullptr){
        vertexStack.push(v_ptr);
        v_ptr = v_ptr->parent;
    }
    while (!vertexStack.empty()){
        Vertex<Data,Key> *topVertex = vertexStack.top();
        ss << topVertex->key;
        vertexStack.pop();

        // If item in stack is not the last item, use arrow
        if (!vertexStack.empty()){
            ss << " -> ";
        }
    }

    // change ss into string and check if u and v are in ss string
    string result = ss.str();

    stringstream u_stringstring;
    stringstream v_stringstring;

    u_stringstring << u;
    v_stringstring << v;

    string u_result = u_stringstring.str();
    string v_result = v_stringstring.str();

    if (result.find(u_result) == string::npos) {
        cout << "";
    }
    else if (result.find(v_result) == string::npos) {
        cout << "";
    }
    else {
        cout << result;
    }

    return;
}



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
