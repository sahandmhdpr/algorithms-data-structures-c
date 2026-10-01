#ifndef ALGORITHMS_DATA_STRUCTURES_C_RECURSION_H
#define ALGORITHMS_DATA_STRUCTURES_C_RECURSION_H

#include <stddef.h>


/* Binary search on a sorted array */
int recursive_binary_search(const int v[],
                            int left,
                            int right,
                            int key);


/* Decimal to binary */
void decimal_to_binary(int value,
                       int binary[],
                       int *n);


/* Recursive power */
float recursive_power(float x, int n);


/* Divide-and-conquer maximum */
int recursive_max(const int v[],
                  int left,
                  int right);


/* Count characters belonging to exception set */
int recursive_count_exceptions(const char *s,
                               const char *exceptions,
                               size_t n_exceptions);


/* Recursive triangle */
void recursive_triangle(int n, int row);


#endif