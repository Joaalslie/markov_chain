#include <stdio.h>
#include <stdlib.h>
#include "markov_chain.h"

struct node{
    int id;
    pointer_t **pointer_array;
};

struct pointer{
    node_t *node_pointer;
    double weight;
};

struct discrete_chain{

    node_t **node_array; // All nodes in the given chain (should be sorted by id number)
    // list_t *transition_list;
};

int verify_nodes(discrete_chain_t *chain){
    // checks if the sum of the probabilities in a node is equal to one, for every node in the chain.

}

/*
 * Checks wether the given id is the id of an existing node in the given chain.
 * Returns a positive integer if so, returns zero if not.
 */
int node_exists(discrete_chain_t *chain, int id){

}

node_t *transition(node_t *node, discrete_chain_t *chain){

}

discrete_chain_t *chain_create(char *file){

}

void chain_destroy(discrete_chain_t *chain){

}

void write_to_file(discrete_chain_t *chain, char *filename){

}

int verify_chain(discrete_chain_t *chain){

}


