#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "markov_chain.h"
#include "json_parser.h"

/*
 * Parses the value received and prints out a message based 
 * on the value. The value is the node number which the chain
 * transitioned to in the last transition.
 */
void parse(int val)
{
    printf("Value: %d\n", val);
    printf("The weather today is: ");
    switch(val)
    {
        case 0:
            // It's sunny..
            printf("Sunny!\n");
            break;

        case 1:
            // It's clouded..
            printf("Clouded!\n");
            break;

        case 2:
            // It's raining..
            printf("Raining!\n");
            break;
        
        default:
            printf("ERROR! Invalid value!\n");
            exit(0);
    }   
}

int main(int argc, char **argv)
{
    int num_elems, dimmensions, start_node;
    discrete_chain_t *chain;
    char scan[10];
    float *matrix;
    time_t t;

    if (argc < 2 || argc > 2)
    {
        printf("Error! Include ONE json file to parse as a chain as argument\n");
        exit(0);
    }
    
    // Retrieve the number of dimmensions in the matrix
    dimmensions = parse_matrix_dimmensions(argv[1]);
    if(dimmensions != 3)
    {
        printf("Error! The matrix needs to have three dimmensional!\n");
        exit(0);
    }

    // Calculate the correct number of elements
    num_elems = dimmensions * dimmensions;
    // Parse the file, finding the node the process starts at
    start_node = parse_start_node(argv[1]);
    // Allocate memory for the array/matrix
    matrix = malloc(sizeof(float) * num_elems);
    // Parse the json-file, adding the elements from the
    // array in the file, to the newly allocated array/matrix
    parse_matrix(argv[1], dimmensions, matrix);
    chain = chain_create(matrix, dimmensions, start_node);
    // initiate randomization
    srand((unsigned long)time(&t));
    printf("To exit, type: X\n\n");
    while(1)
    {
        parse(get_current_node(chain));
        printf("Press . then ENTER to transition..\n");
        scanf("%s", scan);
        if(scan[0] == 'X' && scan[1] == '\0')
            break;
        transition(chain);
    }

    // Destroy the chain before exiting
    chain_destroy(chain);
}