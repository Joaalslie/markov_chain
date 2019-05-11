#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "markov_chain.h"
#include "list.h"

#define MAX_RANDOM_NUMBER 10000

struct node
{
    int id;
    pointer_t **pointer_array;
};

struct pointer
{
    node_t *node_pointer;
    float weight;
};

struct discrete_chain
{
    int num_dim;
    int current_node; //ID of the current node
    unsigned long transition_number;
    node_t **node_array;
    list_t *transition_list;
};

unsigned long generate_random_number(unsigned long max)
{
    return (rand() % max);
}

/*
 * Performs a transition in the markov chain. The current pointer is moved to a new state
 * based on the probabilities of transition in the current node.
 */
node_t *transition(discrete_chain_t *chain)
{
    time_t t;
    int i, j, error_num = 1;
    unsigned long numbers[chain->num_dim];
    unsigned long rand_num;

    // Create an array of numbers based on the probabilities for transition
    for (i = 0; i < chain->num_dim; i++)
    {
        if (i == 0)
        {
            numbers[i] = chain->node_array[chain->current_node]->pointer_array[i]->weight * MAX_RANDOM_NUMBER;
        }
        else
        {
            numbers[i] = numbers[i - 1] + chain->node_array[chain->current_node]->pointer_array[i]->weight * MAX_RANDOM_NUMBER;
        }
    }

    // Generate the random number to perform the transition
    rand_num = generate_random_number(MAX_RANDOM_NUMBER);

    // This loop loops over the array and checks what node
    // to make the transition to based on the random number
    for (j = 0; j < chain->num_dim; j++)
    {
        if (j == 0)
        {
            if (rand_num < numbers[j])
            {
                chain->current_node = j;
                error_num = 0;
                break;
            }
        }
        else
        {
            if (rand_num >= numbers[j - 1] && rand_num < numbers[j])
            {
                chain->current_node = j;
                error_num = 0;
                break;
            }
        }
    }
    if (error_num == 1)
    {
        // Makes sure a transition actually has been made
        printf("ERROR! Couldn't make a transition!\n");
        exit(0);
    }
    list_addlast(chain->transition_list, chain->current_node);
    chain->transition_number++;
}

int get_current_node(discrete_chain_t *chain)
{
    return chain->current_node;
}

list_t *get_transition_list(discrete_chain_t *chain)
{
    return chain->transition_list;
}

/*
 * Writes the resulting transitions in order to a file.
 */
void write_to_file(discrete_chain_t *chain, char *filename)
{
}

/*
 * Helping function which prints the given markov chain.
 * Can be used for debugging, double checking, etc.
 */
void print_chain(discrete_chain_t *chain)
{
    int node_nr, path_nr, i, j;
    float prob;

    for (node_nr = 0; node_nr < chain->num_dim; node_nr++)
    {
        for (path_nr = 0; path_nr < chain->num_dim; j++, path_nr++)
        {
            prob = chain->node_array[node_nr]->pointer_array[path_nr]->weight;
            printf("node nr. %d, to node nr %d, probability: %lf\n", node_nr, path_nr, prob);
        }
    }
    printf("Current node/Starting node: %d\n", chain->current_node);
    printf("Number of transitions: %d\n\n", list_size(chain->transition_list));
}

discrete_chain_t *chain_create(float *matrix, int num_dim, int start)
{
    int i, j, path_nr, node_nr, n_elems;

    n_elems = num_dim * num_dim;

    discrete_chain_t *chain = malloc(sizeof(discrete_chain_t));
    if (chain == NULL)
    {
        printf("Out of memory!\n");
        exit(0);
    }
    chain->num_dim = num_dim;
    chain->node_array = malloc(sizeof(node_t *) * num_dim);
    if (chain->node_array == NULL)
    {
        printf("Out of memory!\n");
        exit(0);
    }

    for (i = 0; i < num_dim; i++)
    {
        chain->node_array[i] = malloc(sizeof(node_t));
        if (chain->node_array[i] == NULL)
        {
            printf("Out of memory!\n");
            exit(0);
            chain->node_array[i]->id = i;
        }
        chain->node_array[i]->pointer_array = malloc(sizeof(pointer_t *) * num_dim);
        if (chain->node_array[i]->pointer_array == NULL)
        {
            printf("Out of memory!\n");
            exit(0);
        }
        for (j = 0; j < num_dim; j++)
        {
            chain->node_array[i]->pointer_array[j] = malloc(sizeof(pointer_t));
            if (chain->node_array[i]->pointer_array[j] == NULL)
            {
                printf("Out of memory!\n");
                exit(0);
            }
        }
    }

    // This nested loop puts the correct weith to the correct path in the markov chain created
    for (node_nr = 0, i = 0; i < n_elems; i += num_dim, node_nr++)
    {
        for (j = i, path_nr = 0; j < (i + num_dim); j++, path_nr++)
        {
            chain->node_array[node_nr]->pointer_array[path_nr]->weight = matrix[j];
            chain->node_array[node_nr]->pointer_array[path_nr]->node_pointer = chain->node_array[j];
        }
    }
    chain->transition_list = list_create();

    chain->current_node = start;

    chain->transition_number = 0;

    verify_chain(chain);
    print_chain(chain);

    return chain;
}

void chain_destroy(discrete_chain_t *chain)
{
    int i, j, path_nr, node_nr, n_elems;

    for (i = 0; i < chain->num_dim; i++)
    {
        for (j = 0; j < chain->num_dim; j++)
        {
            free(chain->node_array[i]->pointer_array[j]);
        }
        free(chain->node_array[i]->pointer_array);
        free(chain->node_array[i]);
    }
    free(chain->node_array);
    free(chain);
}

int verify_chain(discrete_chain_t *chain)
{
    int i, j;
    float sum = 0;

    printf("Verifying markov chain structure..\n");
    for (i = 0; i < chain->num_dim; i++)
    {
        sum = 0;
        for (j = 0; j < chain->num_dim; j++)
        {
            sum += chain->node_array[i]->pointer_array[j]->weight;
        }
        if ((sum - 1.000) > 0.001 || (sum - 1.000) < -0.001)
        {
            printf("Error received when validating the markov chain structure!\n");
            printf("Sum of probabilities in node %d is not 1\n Sum: %lf", i, sum);
            exit(0);
        }
    }
    printf("Markov chain verified. No errors detected!\n\n");

    // Possible extensions:

    /* 
     * Transition through the chain and check if the 
     * transitions correspond to the correct IDs. 
     */

    /*
     * Check if the ID corresponds to the index in the array of nodes
     */
}

void print_transition_list(discrete_chain_t *chain)
{
    print_list(chain->transition_list, chain->transition_number);
}
