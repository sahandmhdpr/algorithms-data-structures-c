#ifndef ALGORITHMS_DATA_STRUCTURES_C_DYNAMIC_ARRAYS_H
#define ALGORITHMS_DATA_STRUCTURES_C_DYNAMIC_ARRAYS_H


/* Creation */
int *array_create(int n);
int *array_create_value(int n, int value);


/* Copying */
int *array_copy(const int *v, int n);
int *array_reverse_copy(const int *v, int n);


/* Filtering */
int *array_filter_even(const int *v, int n, int *new_n);

int *array_greater_than(const int *v,
                        int n,
                        int x,
                        int *new_n);


/* Creating modified copies */
int *array_append(const int *v, int n, int x);

int *array_remove_at(const int *v,
                     int n,
                     int pos);

int *array_insert_at(const int *v,
                     int n,
                     int pos,
                     int x);


/* In-place operations */
int array_remove_at_inplace(int *v,
                            int *n,
                            int pos);

int array_insert_at_inplace(int *v,
                            int *n,
                            int capacity,
                            int pos,
                            int x);


/* Ordered array */
int array_insert_ordered(float *v,
                         int *n,
                         int capacity,
                         float x);


/* Utility */
int array_count_increases(const int *v, int n);

#endif