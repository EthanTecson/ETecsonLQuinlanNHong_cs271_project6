#include "graph.h"
#include <sstream>

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
    distance - -1;
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

