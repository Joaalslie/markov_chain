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
    int current_node;        //Id of the current node pointing at
    node_t **node_array; 
    list_t *transition_list; 
};

/*
 * Performs a transition in the markov chain. The current pointer is moved to a new state
 * based on the probabilities of transition in the current node.
 */
node_t *transition(node_t *node, discrete_chain_t *chain){

}

/*
 * Writes the resulting transitions in order to a file.
 */
void write_to_file(discrete_chain_t *chain, char *filename){

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
    printf("Current node/Starting node: %d\n", chain->current_node);
    printf("Number of transitions: %d\n\n", list_size(chain->transition_list));
}

discrete_chain_t *chain_create(double *matrix, int num_dim, int start){
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

    // This nested loop puts the correct weith to the correct path in the markov chain created
    for(node_nr = 0, i = 0; i < n_elems; i+=num_dim, node_nr++){
        for(j = i, path_nr = 0; j < (i + num_dim); j++, path_nr++){
            chain->node_array[node_nr]->pointer_array[path_nr]->weight = matrix[j];
            chain->node_array[node_nr]->pointer_array[path_nr]->node_pointer = chain->node_array[j];
        }
    }
    chain->transition_list = list_create();

    chain->current_node = start;

    verify_chain(chain);
    print_chain(chain);

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

int verify_chain(discrete_chain_t *chain){
    int i, j;
    double sum = 0;

    printf("Verifying markov chain structure..\n");
    for(i = 0; i < chain->num_dim; i++){
        sum = 0;
        for(j = 0; j < chain->num_dim; j++){
            sum += chain->node_array[i]->pointer_array[j]->weight;
        }
        if((sum - 1.000) > 0.001 || (sum - 1.000) < -0.001){
            printf("Error received when validating the markov chain structure!\n");
            printf("Sum of probabilities in node %d is not 1\n Sum: %lf", i, sum);
            exit(0);
        }
    }
    printf("Markov chain verified. No errors detected!\n\n");

    /* 
     * Possible extension: Transition through the chain and check if the 
     * transitions correspond to the correct id's 
     */
}


