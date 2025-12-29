#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED

typedef struct {
    int size_matrix;
    float **data;
} Matrix;

Matrix *create_matrix(int size_matrix);
Matrix *read_matrix(char *path, int size_matrix);
int find_pivot_row(Matrix *matrix, int col);
float *gauss_jordan_elimination(Matrix *matrix);
float *invert_from_file(const char *path, int n);
void free_matrix(Matrix *matrix);
void get_user_input(Matrix *matrix);
void zero_below_col(Matrix *matrix, int pivot_row, int pivot_col);
void zero_over_col(Matrix *matrix, int pivot_row, int pivot_col);
void swap_rows(Matrix *matrix, int row1, int row2);
void divide_row(Matrix *matrix, int row, float pivot);

#endif // MATRIZ_H_INCLUDED
