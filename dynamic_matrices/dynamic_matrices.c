#include "dynamic_matrices.h"

#include <stdio.h>
#include <stdlib.h>


/* =========================================================
   CREATE MATRIX INITIALIZED TO ZERO
   ========================================================= */

int **matrix_create(int rows, int cols)
{
    int **m;
    int i;
    int j;

    if (rows <= 0 || cols <= 0) {
        return NULL;
    }

    m = malloc(rows * sizeof(int *));

    if (m == NULL) {
        return NULL;
    }

    for (i = 0; i < rows; i++) {

        m[i] = malloc(cols * sizeof(int));

        if (m[i] == NULL) {

            /* Free rows already allocated */
            while (i > 0) {
                i--;
                free(m[i]);
            }

            free(m);

            return NULL;
        }

        for (j = 0; j < cols; j++) {
            m[i][j] = 0;
        }
    }

    return m;
}


/* =========================================================
   CREATE MATRIX INITIALIZED TO A VALUE
   ========================================================= */

int **matrix_create_value(int rows,
                          int cols,
                          int value)
{
    int **m;
    int i;
    int j;

    if (rows <= 0 || cols <= 0) {
        return NULL;
    }

    m = malloc(rows * sizeof(int *));

    if (m == NULL) {
        return NULL;
    }

    for (i = 0; i < rows; i++) {

        m[i] = malloc(cols * sizeof(int));

        if (m[i] == NULL) {

            while (i > 0) {
                i--;
                free(m[i]);
            }

            free(m);

            return NULL;
        }

        for (j = 0; j < cols; j++) {
            m[i][j] = value;
        }
    }

    return m;
}


/* =========================================================
   DEEP COPY
   ========================================================= */

int **matrix_copy(int **m,
                  int rows,
                  int cols)
{
    int **copy;
    int i;
    int j;

    if (m == NULL ||
        rows <= 0 ||
        cols <= 0) {

        return NULL;
    }

    copy = malloc(rows * sizeof(int *));

    if (copy == NULL) {
        return NULL;
    }

    for (i = 0; i < rows; i++) {

        copy[i] = malloc(cols * sizeof(int));

        if (copy[i] == NULL) {

            while (i > 0) {
                i--;
                free(copy[i]);
            }

            free(copy);

            return NULL;
        }

        for (j = 0; j < cols; j++) {
            copy[i][j] = m[i][j];
        }
    }

    return copy;
}


/* =========================================================
   FILL EXISTING MATRIX
   ========================================================= */

void matrix_fill(int **m,
                 int rows,
                 int cols,
                 int value)
{
    int i;
    int j;

    if (m == NULL ||
        rows <= 0 ||
        cols <= 0) {

        return;
    }

    for (i = 0; i < rows; i++) {

        if (m[i] == NULL) {
            continue;
        }

        for (j = 0; j < cols; j++) {
            m[i][j] = value;
        }
    }
}


/* =========================================================
   PRINT MATRIX
   ========================================================= */

void matrix_print(int **m,
                  int rows,
                  int cols)
{
    int i;
    int j;

    if (m == NULL ||
        rows <= 0 ||
        cols <= 0) {

        return;
    }

    for (i = 0; i < rows; i++) {

        if (m[i] == NULL) {
            continue;
        }

        for (j = 0; j < cols; j++) {
            printf("%d ", m[i][j]);
        }

        printf("\n");
    }
}


/* =========================================================
   FREE MATRIX
   ========================================================= */

void matrix_free(int **m, int rows)
{
    int i;

    if (m == NULL) {
        return;
    }

    for (i = 0; i < rows; i++) {
        free(m[i]);
    }

    free(m);
}