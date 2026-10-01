#include "recursion.h"

#include <stdio.h>


/* =========================================================
   RECURSIVE BINARY SEARCH

   Array must already be sorted.
   Returns index of key or -1 if not found.
   ========================================================= */

int recursive_binary_search(const int v[],
                            int left,
                            int right,
                            int key)
{
    int middle;

    if (v == NULL || left > right) {
        return -1;
    }

    middle = left + (right - left) / 2;

    if (v[middle] == key) {
        return middle;
    }

    if (key < v[middle]) {
        return recursive_binary_search(v,
                                       left,
                                       middle - 1,
                                       key);
    }

    return recursive_binary_search(v,
                                   middle + 1,
                                   right,
                                   key);
}


/* =========================================================
   DECIMAL TO BINARY

   Example:
   value = 13

   binary becomes:
   1 1 0 1

   *n contains the number of binary digits.
   ========================================================= */

void decimal_to_binary(int value,
                       int binary[],
                       int *n)
{
    if (binary == NULL || n == NULL) {
        return;
    }

    if (value == 0) {
        return;
    }

    decimal_to_binary(value / 2,
                      binary,
                      n);

    binary[*n] = value % 2;

    (*n)++;
}


/* =========================================================
   RECURSIVE POWER

   Supports:
   positive exponent
   zero exponent
   negative exponent
   ========================================================= */

float recursive_power(float x, int n)
{
    if (n == 0) {
        return 1.0f;
    }

    if (n > 0) {
        return x * recursive_power(x, n - 1);
    }

    return (1.0f / x) *
           recursive_power(x, n + 1);
}


/* =========================================================
   DIVIDE-AND-CONQUER MAXIMUM
   ========================================================= */

int recursive_max(const int v[],
                  int left,
                  int right)
{
    int middle;
    int max_left;
    int max_right;

    if (left == right) {
        return v[left];
    }

    middle = left + (right - left) / 2;

    max_left = recursive_max(v,
                             left,
                             middle);

    max_right = recursive_max(v,
                              middle + 1,
                              right);

    if (max_left > max_right) {
        return max_left;
    }

    return max_right;
}


/* =========================================================
   COUNT EXCEPTION CHARACTERS

   Counts how many characters in s occur inside
   the exceptions array.

   Example:

   s = "algorithm"
   exceptions = {'a', 'i', 'o'}

   result = 3
   ========================================================= */

int recursive_count_exceptions(const char *s,
                               const char *exceptions,
                               size_t n_exceptions)
{
    size_t i;
    int found;

    if (s == NULL ||
        exceptions == NULL ||
        *s == '\0') {

        return 0;
    }

    found = 0;

    for (i = 0; i < n_exceptions; i++) {

        if (*s == exceptions[i]) {
            found = 1;
            break;
        }
    }

    return found +
           recursive_count_exceptions(s + 1,
                                      exceptions,
                                      n_exceptions);
}


/* =========================================================
   RECURSIVE TRIANGLE

   recursive_triangle(4, 1)

   prints:

   1
   22
   333
   4444
   ========================================================= */

void recursive_triangle(int n, int row)
{
    int i;

    if (row > n) {
        return;
    }

    for (i = 0; i < row; i++) {
        printf("%d", row);
    }

    printf("\n");

    recursive_triangle(n, row + 1);
}