#include <stdio.h>
#include <json-c/json.h>
#include <math.h>

#include "markov_chain.h"

void verify_matrix(int n_elems, int dimmensions, double *matrix){

    printf("Verifying markov chain/matrix..\n");
    int i, j;
    double sum = 0.0;
    int d = dimmensions * dimmensions;

    if(n_elems != d){
        printf("ERROR! matrix must be squared!\n");
        exit(0);
    }
    else{
        for(i = 0; i < n_elems; i+=dimmensions){
            for(j = i; j < (i + dimmensions); j++){
                sum += matrix[j];
            }
            // Need to compare, to a value close to zero, since it's hard to compare doubles..
            if((sum - 1.000) > 0.001 || (sum - 1.000) < -0.001){
                printf("ERROR! The sum of a row in the matrix must always be 1.0!\n");
                exit(0);
            } else{
                sum = 0.0;
            }
        }
    }
    printf("Matrix verified! no errors detected!\n");
}

int main(int argc, char **argv){

    struct json_object *parsed_json;
    struct json_object *dimmensions;
    struct json_object *matrix;
    struct json_object *elem;

    int dim_num;

    size_t n_elems;
    size_t i;

    FILE *fp;
    char buffer[2048];


    if(argc < 2 && argc > 2){
        printf("Include only one json file to parse as a chain as argument\n");
        exit(0);
    }

    fp = fopen(argv[1], "r");
    fread(buffer, 2048, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);

    json_object_object_get_ex(parsed_json, "num_dim", &dimmensions);
    json_object_object_get_ex(parsed_json, "matrix", &matrix);

    dim_num = json_object_get_int(dimmensions);
    double dim_num_d =json_object_get_double(dimmensions);

    n_elems = json_object_array_length(matrix);
    double elements[n_elems];

    for(i = 0; i < n_elems; i++){
        elem = json_object_array_get_idx(matrix, i);
        elements[i] = json_object_get_double(elem);
    }
    
    verify_matrix((int)n_elems, (int)dim_num_d, elements);

}
