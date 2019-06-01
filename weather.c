#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "markov_chain.h"
#include "json_parser.h"

void parse(char *buffer, int val)
{
    switch(val)
    {
        case 0:
            // Weather is sunny.

        case 1:
            // Weather is cloudy.

        case 2:
            // Weather is rainy.
    }   
}

int main(int argc, char **argv)
{
    int num_elems, dimmensions, start_node;
    discrete_chain_t *chain;
    char buffer[20];
    float *matrix;
    char scan;
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
    matrix = malloc(sizeof(float) * num_elems);

    // Parse the json-file, adding the elements from the
    // array in the file, to the newly allocated array/matrix
    parse_matrix(argv[1], dimmensions, matrix);

    chain = chain_create(matrix, dimmensions, start_node);

    // initiate randomization
    srand((unsigned long)time(&t));

    printf("To exit, type: X\n");
    parse(buffer, get_current_node(chain));
    printf("Initially, the weather is: %s\n", buffer);
    while(1)
    {
        printf("Press ENTER to transition..\n");
        scanf("%c", scan);
        if(scan == 'X')
            break;
        transition(chain);
        parse(buffer, get_current_node(chain));
        printf("The weather today is: %s\n", buffer);
    }
}