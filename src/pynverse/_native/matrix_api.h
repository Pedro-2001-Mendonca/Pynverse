#ifndef MATRIX_API_H
#define MATRIX_API_H

float *invert_from_file(const char *path, int size_matrix);
float *invert_from_array(float *arr, int size_matrix);
void free_matrix_data(float *data);

#endif