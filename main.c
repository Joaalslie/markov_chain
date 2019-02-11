#include <stdio.h>
#include <json-c/json.h>
#include <math.h>

#include "markov_chain.h"

void verify_matrix(int n_elems, int dimmensions, double *matrix){

    printf("Verifying markov chain/matrix..\n");
    int i, j;
    double sum = 0;
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
            if(sum != 1){
                printf("ERROR! The sum of a row int he matrix must always be zero!\n");
                exit(0);
            } else{
                sum = 0;
            }
        }
    }
    printf("Matrix verified! no errors detected!\n");
}

int main(int argc, char **argv){
    FILE *fp;
    char buffer[2048];

    struct json_object *parsed_json;
    struct json_object *dimmensions;
    struct json_object *rows;
    struct json_object *elem;

    int dim_num;

    size_t n_elems;
    size_t i;

    if(argc < 2 && argc > 2){
        printf("Include only one json file to parse as a chain as argument\n");
        exit(0);
    }

    fp = fopen(argv[1], "r");
    fread(buffer, 2048, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);

    json_object_object_get_ex(parsed_json, "num_dim", &dimmensions);
    json_object_object_get_ex(parsed_json, "rows", &rows);

    dim_num = json_object_get_int(dimmensions);
    double dim_num_d =json_object_get_double(dimmensions);

    n_elems = json_object_array_length(rows);
    double elements[n_elems];

    printf("dimmension size: %d\n", dim_num);

    for(i = 0; i < n_elems; i++){
        elem = json_object_array_get_idx(rows, i);
        elements[i] = json_object_get_double(elem);
    }

    for(int j = 0; j < n_elems; j++){
        printf("%d : %f\n", j+1, elements[j]);
    }
    verify_matrix((int)n_elems, (int)dim_num_d, elements);

}
