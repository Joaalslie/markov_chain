#include <stdio.h>
#include <stdlib.h>
#include "markov_chain.h"
#include "list.h"

struct node{
    int id;
    pointer_t **pointer_array;
};

struct pointer{
    node_t *node_pointer;
    double weight;
};

struct discrete_chain{
    int num_dim; 
    node_t **node_array; // All nodes in the given chain (should be sorted by id number)
    list_t *transition_list; 
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

/*
 * Helping function which prints the given markov chain.
 * Can be used for debugging, double checking, etc.
 */
void print_chain(discrete_chain_t *chain){
    int node_nr, path_nr, i, j;
    double prob;

    for(node_nr = 0; node_nr < chain->num_dim; node_nr++){
        for(path_nr = 0; path_nr < chain->num_dim; j++, path_nr++){
            prob = chain->node_array[node_nr]->pointer_array[path_nr]->weight;
            printf("node nr. %d, to node nr %d, probability: %lf\n", node_nr, path_nr, prob);
        }
    }
}

discrete_chain_t *chain_create(double *matrix, int num_dim){
    int i, j, path_nr, node_nr, n_elems;

    n_elems = num_dim * num_dim;
    
    discrete_chain_t *chain = malloc(sizeof(discrete_chain_t));
    if(chain == NULL){
        printf("Out of memory!\n");
        exit(0);
    }
    chain->num_dim = num_dim;
    chain->node_array = malloc(sizeof(node_t *) * num_dim);
    if(chain->node_array == NULL){
        printf("Out of memory!\n");
        exit(0);
    }

    for(i = 0; i < num_dim; i++){
        chain->node_array[i] = malloc(sizeof(node_t));
        if(chain->node_array[i] == NULL){
            printf("Out of memory!\n");
            exit(0);
        chain->node_array[i]->id = i;
        }
        chain->node_array[i]->pointer_array = malloc(sizeof(pointer_t *) * num_dim);
        if(chain->node_array[i]->pointer_array == NULL){
            printf("Out of memory!\n");
            exit(0);
        }
        for(j = 0; j < num_dim; j++){
            chain->node_array[i]->pointer_array[j] = malloc(sizeof(pointer_t));
            if(chain->node_array[i]->pointer_array[j] == NULL){
                printf("Out of memory!\n");
                exit(0);
            }
        }
    }

    // This nested loop goes puts the correct weith to the correct path in the markov chain created
    for(node_nr = 0, i = 0; i < n_elems; i+=num_dim, node_nr++){
        for(j = i, path_nr = 0; j < (i + num_dim); j++, path_nr++){
            chain->node_array[node_nr]->pointer_array[path_nr]->weight = matrix[j];
            chain->node_array[node_nr]->pointer_array[path_nr]->node_pointer = chain->node_array[j];
        }
    }
    print_chain(chain);

    chain->transition_list = list_create();

    return chain;
}

void chain_destroy(discrete_chain_t *chain){
    int i, j, path_nr, node_nr, n_elems;

    for(i = 0; i < chain->num_dim; i++){
        for(j = 0; j < chain->num_dim; j++){
            free(chain->node_array[i]->pointer_array[j]);
        }
        free(chain->node_array[i]->pointer_array);
        free(chain->node_array[i]);
    }
    free(chain->node_array);
    free(chain);
}

void write_to_file(discrete_chain_t *chain, char *filename){

}

int verify_chain(discrete_chain_t *chain){

}


