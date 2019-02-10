#include <stdio.h>
#include <json-c/json.h>

#include "markov_chain.h"

int verify_matrix(size_t n_elems, double dimmensions){

    double number = (double)n_elems;

    if(number != dimmensions){
        return -1;
    }
    else{
        return 1;
    }
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
    if(verify_matrix(n_elems, dim_num_d) == -1){
        printf("Error! verify_matrix returned -1\n");
        exit(0);
    }

}
