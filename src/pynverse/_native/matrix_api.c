#include <stdlib.h>
#include "matriz.h"
#include "matrix_api.h"

float *invert_from_array(float *arr, int size_matrix){

    Matrix *matrix = create_matrix(size_matrix);

    if(!matrix)
        return NULL;

    for(int i=0; i<size_matrix; i++){

        for(int j=0; j<size_matrix; j++){

            *(*(matrix->data+i)+j) = *(arr + (i*size_matrix) + j);

        }
    }

    float *inverse = gauss_jordan_elimination(matrix);

    if(!inverse)
        return NULL;

    return inverse;
}

float *invert_from_file(const char *path, int size_matrix){

    Matrix *matrix = read_matrix((char*)path, size_matrix);

    if(!matrix)
        return NULL;

    float *inverse = gauss_jordan_elimination(matrix);

    if(!inverse)
        return NULL;

    return inverse;
}

void free_matrix_data(float *data){
    free(data);
}