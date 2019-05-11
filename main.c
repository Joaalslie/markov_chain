#include <json-c/json.h>
#include <unistd.h> // for using atoi() to convert char to int
#include <stdio.h>
#include <math.h>

#include <time.h>

#include "markov_chain.h"

#define BUFFER_SIZE 2048

/*
 * Verifies the matrix, printing errors and exiting the program 
 * if there is a problem.
 */
void verify_matrix(int n_elems, int dimmensions, float *matrix)
{

    printf("Verifying markov chain/matrix..\n");
    int i, j;
    float sum = 0.0;
    int d = dimmensions * dimmensions;

    // Checks if the squared dimmension-number of the matrix is equal to it's elements
    if (n_elems != d)
    {
        printf("ERROR! matrix must be squared!\nIf the matrix is squared, check that the you have set the correct dimmension value!\n");
        exit(0);
    }
    else
    {
        // For-loop looping through the rows columns of the matrix
        for (i = 0; i < n_elems; i += dimmensions)
        {
            // For-loop looping through the rows of the matrix
            for (j = i; j < (i + dimmensions); j++)
            {
                sum += matrix[j];
            }
            // Need to compare, to a value close to zero, since it's hard to compare exact floats..
            if ((sum - 1.000) > 0.001 || (sum - 1.000) < -0.001)
            {
                printf("ERROR! The sum of a row in the matrix must always be 1.0!\n");
                exit(0);
            }
            else
            {
                // The sum needs to be reset, since we're moving to next row..
                sum = 0.0;
            }
        }
    }
    // Reaching this spot means no errors was detected.
    printf("Matrix verified! no errors detected!\n\n");
}

/*
 * Parses the given json-file and fills up the given array/matrix with
 * elements in the order given in the json-file. Also calls to verify the array. 
 */
void parse_matrix(char *filename, int dimmension_size, float *elements)
{

    struct json_object *parsed_json;
    struct json_object *matrix;
    struct json_object *elem;

    int dim_num;

    size_t n_elems;
    size_t i;

    FILE *fp;
    char buffer[BUFFER_SIZE];

    // Open and read the file, putting the info in a buffer.
    fp = fopen(filename, "r");
    fread(buffer, BUFFER_SIZE, 1, fp);
    fclose(fp);

    // Parses the buffer into a json-struct
    parsed_json = json_tokener_parse(buffer);

    // Retrieves the array, sending it to a json-struct
    json_object_object_get_ex(parsed_json, "matrix", &matrix);

    // Retrieves the lenght of the array
    n_elems = json_object_array_length(matrix);

    for (i = 0; i < n_elems; i++)
    {
        // Retrieves the element on the indexed spot in the array
        // Then passes it to the allocated array given in the function call
        elem = json_object_array_get_idx(matrix, i);
        elements[i] = (float)json_object_get_double(elem);
    }
    // Verifies the array
    verify_matrix((int)n_elems, dimmension_size, elements);
}

/*
 * Parses the given file, retrieving the number
 * of dimmensions from the given json-file.  
 */
int parse_matrix_dimmensions(char *filename)
{
    struct json_object *parsed_json;
    struct json_object *dimmensions;
    char buffer[BUFFER_SIZE];
    int dim_num;
    FILE *fp;

    // Open and read the file, putting the info in a buffer.
    fp = fopen(filename, "r");
    fread(buffer, BUFFER_SIZE, 1, fp);
    fclose(fp);

    // Parses the buffer into a json-struct
    parsed_json = json_tokener_parse(buffer);
    // Retrieves the number of dimmensions in the matrix to a json-struct
    json_object_object_get_ex(parsed_json, "num_dim", &dimmensions);

    // Retrieves the dimmension number of type int
    // Then returns it
    dim_num = json_object_get_int(dimmensions);
    return dim_num;
}

int parse_start_node(char *filename)
{
    struct json_object *parsed_json;
    struct json_object *start;
    char buffer[BUFFER_SIZE];
    int start_node;
    FILE *fp;

    // Open and read the file, putting the info in a buffer.
    fp = fopen(filename, "r");
    fread(buffer, BUFFER_SIZE, 1, fp);
    fclose(fp);

    // Parses the buffer into a json-struct
    parsed_json = json_tokener_parse(buffer);
    // Retrieves the number of dimmensions in the matrix to a json-struct
    json_object_object_get_ex(parsed_json, "start", &start);

    start_node = json_object_get_int(start);
    return start_node;
}

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
