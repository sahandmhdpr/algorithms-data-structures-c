#ifndef ALGORITHMS_DATA_STRUCTURES_C_DYNAMIC_MATRICES_H
#define ALGORITHMS_DATA_STRUCTURES_C_DYNAMIC_MATRICES_H


/* Creation */
int **matrix_create(int rows, int cols);

int **matrix_create_value(int rows,
                          int cols,
                          int value);


/* Copy */
int **matrix_copy(int **m,
                  int rows,
                  int cols);


/* Utility operations */
void matrix_fill(int **m,
                 int rows,
                 int cols,
                 int value);

void matrix_print(int **m,
                  int rows,
                  int cols);


/* Deallocation */
void matrix_free(int **m, int rows);


#endif