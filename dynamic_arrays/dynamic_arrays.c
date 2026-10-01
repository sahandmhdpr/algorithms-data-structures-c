#include "dynamic_arrays.h"

#include <stdlib.h>


/* =========================================================
   CREATION
   ========================================================= */

int *array_create(int n)
{
    int *v;
    int i;

    if (n <= 0) {
        return NULL;
    }

    v = malloc(n * sizeof(int));

    if (v == NULL) {
        return NULL;
    }

    for (i = 0; i < n; i++) {
        v[i] = 0;
    }

    return v;
}


int *array_create_value(int n, int value)
{
    int *v;
    int i;

    if (n <= 0) {
        return NULL;
    }

    v = malloc(n * sizeof(int));

    if (v == NULL) {
        return NULL;
    }

    for (i = 0; i < n; i++) {
        v[i] = value;
    }

    return v;
}


/* =========================================================
   COPY
   ========================================================= */

int *array_copy(const int *v, int n)
{
    int *copy;
    int i;

    if (v == NULL || n <= 0) {
        return NULL;
    }

    copy = malloc(n * sizeof(int));

    if (copy == NULL) {
        return NULL;
    }

    for (i = 0; i < n; i++) {
        copy[i] = v[i];
    }

    return copy;
}


int *array_reverse_copy(const int *v, int n)
{
    int *copy;
    int i;

    if (v == NULL || n <= 0) {
        return NULL;
    }

    copy = malloc(n * sizeof(int));

    if (copy == NULL) {
        return NULL;
    }

    for (i = 0; i < n; i++) {
        copy[i] = v[n - 1 - i];
    }

    return copy;
}


/* =========================================================
   FILTERING
   ========================================================= */

int *array_filter_even(const int *v,
                       int n,
                       int *new_n)
{
    int *result;
    int count;
    int i;
    int j;

    if (new_n == NULL) {
        return NULL;
    }

    *new_n = 0;

    if (v == NULL || n <= 0) {
        return NULL;
    }

    count = 0;

    for (i = 0; i < n; i++) {

        if (v[i] % 2 == 0) {
            count++;
        }
    }

    if (count == 0) {
        return NULL;
    }

    result = malloc(count * sizeof(int));

    if (result == NULL) {
        return NULL;
    }

    j = 0;

    for (i = 0; i < n; i++) {

        if (v[i] % 2 == 0) {
            result[j] = v[i];
            j++;
        }
    }

    *new_n = count;

    return result;
}


int *array_greater_than(const int *v,
                        int n,
                        int x,
                        int *new_n)
{
    int *result;
    int count;
    int i;
    int j;

    if (new_n == NULL) {
        return NULL;
    }

    *new_n = 0;

    if (v == NULL || n <= 0) {
        return NULL;
    }

    count = 0;

    for (i = 0; i < n; i++) {

        if (v[i] > x) {
            count++;
        }
    }

    if (count == 0) {
        return NULL;
    }

    result = malloc(count * sizeof(int));

    if (result == NULL) {
        return NULL;
    }

    j = 0;

    for (i = 0; i < n; i++) {

        if (v[i] > x) {
            result[j] = v[i];
            j++;
        }
    }

    *new_n = count;

    return result;
}


/* =========================================================
   MODIFIED COPIES
   ========================================================= */

int *array_append(const int *v, int n, int x)
{
    int *result;
    int i;

    if (n < 0) {
        return NULL;
    }

    if (n > 0 && v == NULL) {
        return NULL;
    }

    result = malloc((n + 1) * sizeof(int));

    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < n; i++) {
        result[i] = v[i];
    }

    result[n] = x;

    return result;
}


int *array_remove_at(const int *v,
                     int n,
                     int pos)
{
    int *result;
    int i;
    int j;

    if (v == NULL ||
        n <= 1 ||
        pos < 0 ||
        pos >= n) {

        return NULL;
    }

    result = malloc((n - 1) * sizeof(int));

    if (result == NULL) {
        return NULL;
    }

    j = 0;

    for (i = 0; i < n; i++) {

        if (i != pos) {
            result[j] = v[i];
            j++;
        }
    }

    return result;
}


int *array_insert_at(const int *v,
                     int n,
                     int pos,
                     int x)
{
    int *result;
    int i;
    int j;

    if (n < 0 ||
        pos < 0 ||
        pos > n) {

        return NULL;
    }

    if (n > 0 && v == NULL) {
        return NULL;
    }

    result = malloc((n + 1) * sizeof(int));

    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < pos; i++) {
        result[i] = v[i];
    }

    result[pos] = x;

    j = pos + 1;

    for (i = pos; i < n; i++) {
        result[j] = v[i];
        j++;
    }

    return result;
}


/* =========================================================
   IN-PLACE REMOVE
   ========================================================= */

int array_remove_at_inplace(int *v,
                            int *n,
                            int pos)
{
    int i;

    if (v == NULL ||
        n == NULL ||
        *n <= 0 ||
        pos < 0 ||
        pos >= *n) {

        return 0;
    }

    for (i = pos; i < *n - 1; i++) {
        v[i] = v[i + 1];
    }

    (*n)--;

    return 1;
}


/* =========================================================
   IN-PLACE INSERT
   ========================================================= */

int array_insert_at_inplace(int *v,
                            int *n,
                            int capacity,
                            int pos,
                            int x)
{
    int i;

    if (v == NULL ||
        n == NULL ||
        *n < 0 ||
        *n >= capacity ||
        pos < 0 ||
        pos > *n) {

        return 0;
    }

    for (i = *n; i > pos; i--) {
        v[i] = v[i - 1];
    }

    v[pos] = x;

    (*n)++;

    return 1;
}


/* =========================================================
   ORDERED INSERTION

   Your exam/practice pattern:
   find the insertion position,
   shift elements right,
   insert x,
   increase number of elements.
   ========================================================= */

int array_insert_ordered(float *v,
                         int *n,
                         int capacity,
                         float x)
{
    int i;
    int pos;

    if (v == NULL ||
        n == NULL ||
        *n < 0 ||
        *n >= capacity) {

        return 0;
    }

    pos = 0;

    while (pos < *n && v[pos] < x) {
        pos++;
    }

    for (i = *n; i > pos; i--) {
        v[i] = v[i - 1];
    }

    v[pos] = x;

    (*n)++;

    return 1;
}


/* =========================================================
   COUNT INCREASES

   Counts positions for which:
   v[i + 1] > v[i]
   ========================================================= */

int array_count_increases(const int *v, int n)
{
    int count;
    int i;

    if (v == NULL || n <= 1) {
        return 0;
    }

    count = 0;

    for (i = 0; i < n - 1; i++) {

        if (v[i + 1] > v[i]) {
            count++;
        }
    }

    return count;
}