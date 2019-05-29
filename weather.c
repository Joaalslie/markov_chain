#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "markov_chain.h"
#include "json_parser.h"

int main(int argc, char **argv)
{
    int num_elems, dimmensions, start_node;
    time_t t;

    if (argc < 2 || argc > 2)
    {
        printf("Error! Include ONE json file to parse as a chain as argument\n");
        exit(0);
    }
    // Retrieve the number of dimmensions in the matrix
    dimmensions = parse_matrix_dimmensions(argv[1]);

    // Calculate the correct number of elements
    num_elems = dimmensions * dimmensions;

    // Parse the file, finding the node the process starts at
    start_node = parse_start_node(argv[1]);

    // Allocate memory for the array/matrix
    float *matrix = malloc(sizeof(float) * num_elems);

    // Parse the json-file, adding the elements from the
    // array in the file, to the newly allocated array/matrix
    parse_matrix(argv[1], dimmensions, matrix);

    discrete_chain_t *chain = chain_create(matrix, dimmensions, start_node);

    // initiate randomization
    srand((unsigned long)time(&t));

}