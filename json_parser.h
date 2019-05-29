#ifndef JSON_PARSER_H
#define JSON_PARSER_H

/*
 * Verifies the matrix, printing errors and exiting the program 
 * if there is a problem.
 */
void verify_matrix(int n_elems, int dimmensions, float *matrix);

/*
 * Parses the given json-file and fills up the given array/matrix with
 * elements in the order given in the json-file. Also calls to verify the array. 
 */
void parse_matrix(char *filename, int dimmension_size, float *elements);

/*
 * Parses the given file, retrieving the number
 * of dimmensions from the given json-file.  
 */
int parse_matrix_dimmensions(char *filename);

/*
 * Parses the start position (x0) from the json file.
 */
int parse_start_node(char *filename);

#endif /* JSON_PARSER_H */