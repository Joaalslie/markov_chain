#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "markov_chain.h"
#include "json_parser.h"

#define BUFFER_SIZE 2048

int main(int argc, char **argv)
{

    int num_elems, dimmensions, start_node, i;
    char *file_name; //Name of the file to write to
    FILE *fp;
    time_t t;

    if (argc < 3 || argc > 3)
    {
        printf("Error! Include ONE json file to parse as a chain as argument\n");
        printf("Also include a filename of which to write the information to!\n");
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

    // Prepare to print information to file
    file_name = argv[2];
    fp = fopen(file_name, "w");

    // Print to file as transitions is performed
    fprintf(fp, "%d\n", get_current_node(chain));
    for (i = 0; i < 100; i++)
    {
        transition(chain);
        fprintf(fp, "%d\n", get_current_node(chain));
    }

    print_transition_list(chain);

    fclose(fp);
    chain_destroy(chain);
}
