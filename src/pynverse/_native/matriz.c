#include "matriz.h"
#include "math.h"
#include <stdlib.h>
#include <stdio.h>

Matrix *read_matrix(char* path, int size_matrix){

    FILE *fp = fopen(path, "r");

    if(!fp){
        perror("ERROR: Unable to open file, please check the path/name of your file.");
        return NULL;
    }

    Matrix *matrix = create_matrix(size_matrix);

    for(int i=0; i<size_matrix; i++){

        for(int j=0; j<size_matrix; j++){

            if(fscanf(fp, "%f", (*(matrix->data+i)+j)) != 1){

                printf("ERROR: Unable to read element [%d][%d], ending execution.", i, j);
                fclose(fp);
                return NULL;

            }
        }
    }

    fclose(fp);

    return matrix;

}

void swap_rows(Matrix *matrix, int row1, int row2){

    float *temp = *(matrix->data+row1);
    (*(matrix->data+row1)) = *(matrix->data+row2);
    (*(matrix->data+row2)) = temp;

}

int find_pivot_row(Matrix *matrix, int col){

    for(int i=col; i<matrix->size_matrix; i++){

        if(*(*(matrix->data+i)+col) != 0)
            return i;

    }

    return -1;
}

float *gauss_jordan_elimination(Matrix *matrix){

   for(int j=0; j<matrix->size_matrix; j++){

    int pivot_row = find_pivot_row(matrix, j);

    if (pivot_row == -1){
        printf("ERROR: Unable to find a row with pivot not equal to zero.\n");
        return NULL;
    }

    if(pivot_row != j)
        swap_rows(matrix, j, pivot_row);

    float pivot = *(*(matrix->data+j)+j);

    divide_row(matrix, j, pivot);

    zero_below_col(matrix, j, j);

   }

   for(int j = matrix->size_matrix-1; j>=0; j--){

    zero_over_col(matrix, j, j);

   }

   float* inverse = malloc(matrix->size_matrix * matrix->size_matrix * sizeof(float));

   for(int i=0; i<matrix->size_matrix; i++){

    for(int j=0; j<matrix->size_matrix; j++){

        *(inverse + i*matrix->size_matrix + j) = *(*(matrix->data+i)+j+matrix->size_matrix);

    }

   }

   free_matrix(matrix);

   return inverse;

}

void divide_row(Matrix *matrix, int row, float pivot){

    if (pivot == 0.0f){
        printf("ERROR: division by zero in the pivot normalization.\n");
    }

    for(int j=0; j<2*matrix->size_matrix; j++){
        *(*(matrix->data+row)+j) /= pivot;
    }

}

void zero_below_col(Matrix *matrix, int pivot_row, int pivot_col){

   for(int i=pivot_row+1; i<matrix->size_matrix; i++){

        float factor = *(*(matrix->data+i)+pivot_col);

        for(int j=0; j<matrix->size_matrix*2; j++){

            *(*(matrix->data+i)+j) -= *(*(matrix->data+pivot_row)+j) * factor;

        }

   }

}

void zero_over_col(Matrix *matrix, int pivot_row, int pivot_col){

    for(int i=pivot_row-1; i >= 0; i--){

        float factor = *(*(matrix->data+i)+pivot_col);

        for(int j=0; j<2*matrix->size_matrix; j++){
            *(*(matrix->data+i)+j) -= *(*(matrix->data+pivot_row)+j) * factor;
        }
    }
}

void get_user_input(Matrix *matrix){
    //Basic input read from the user to populate the matrix
    for(int i =0; i<matrix->size_matrix;i++){

        for(int j = 0; j<matrix->size_matrix;j++){

            printf("Insert the value of the element [%d][%d]: ", i, j);
            scanf("%f", (*(matrix->data+i)+j));
            printf("\n");

        }
    }
}

Matrix *create_matrix(int size_matrix){
    //Allocate bytes for the matrix
    Matrix *matrix = malloc(sizeof(Matrix));

    matrix->size_matrix = size_matrix;
    matrix->data = malloc(size_matrix * sizeof(float*)); //Matrix has "size_matrix" rows

    //Each row has "2 * size_matrix" cols allocated to it (because of the identity at the end of it)
    for(int i=0; i<size_matrix; i++){
        *(matrix->data+i) = malloc(2 * size_matrix * sizeof(float));
    }

    //Initialize identity matrix at the end of the original matrix
    for(int i=0; i<size_matrix; i++){

        for(int j=size_matrix; j<2*size_matrix; j++){

            if(i == (j-size_matrix)){

                *(*(matrix->data+i)+j) = 1.0;
                continue;

            }

            *(*(matrix->data+i)+j) = 0.0;

        }
    }

    return matrix;
}

void free_matrix(Matrix *matrix){

    if (matrix == NULL) return;

    for(int i=0; i<matrix->size_matrix;i++){
        free(*(matrix->data+i));
    }

    free(matrix);
}
