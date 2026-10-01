#include "strings.h"

#include <ctype.h>
#include <stdlib.h>


/* =========================================================
   COPY STRING
   ========================================================= */

char *string_copy(const char *s)
{
    char *copy;
    int length;
    int i;

    if (s == NULL) {
        return NULL;
    }

    length = 0;

    while (s[length] != '\0') {
        length++;
    }

    copy = malloc((length + 1) * sizeof(char));

    if (copy == NULL) {
        return NULL;
    }

    for (i = 0; i < length; i++) {
        copy[i] = s[i];
    }

    copy[length] = '\0';

    return copy;
}


/* =========================================================
   CONCATENATE TWO STRINGS
   ========================================================= */

char *string_concat(const char *s1,
                    const char *s2)
{
    char *result;
    int length1;
    int length2;
    int i;
    int j;

    if (s1 == NULL || s2 == NULL) {
        return NULL;
    }

    length1 = 0;
    length2 = 0;

    while (s1[length1] != '\0') {
        length1++;
    }

    while (s2[length2] != '\0') {
        length2++;
    }

    result = malloc((length1 + length2 + 1) * sizeof(char));

    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < length1; i++) {
        result[i] = s1[i];
    }

    j = length1;

    for (i = 0; i < length2; i++) {
        result[j] = s2[i];
        j++;
    }

    result[length1 + length2] = '\0';

    return result;
}


/* =========================================================
   REVERSE STRING - NEW COPY
   ========================================================= */

char *string_reverse(const char *s)
{
    char *result;
    int length;
    int i;

    if (s == NULL) {
        return NULL;
    }

    length = 0;

    while (s[length] != '\0') {
        length++;
    }

    result = malloc((length + 1) * sizeof(char));

    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < length; i++) {
        result[i] = s[length - 1 - i];
    }

    result[length] = '\0';

    return result;
}


/* =========================================================
   REMOVE SPACES
   ========================================================= */

char *string_remove_spaces(const char *s)
{
    char *result;
    int length;
    int count;
    int i;
    int j;

    if (s == NULL) {
        return NULL;
    }

    length = 0;
    count = 0;

    while (s[length] != '\0') {

        if (s[length] != ' ') {
            count++;
        }

        length++;
    }

    result = malloc((count + 1) * sizeof(char));

    if (result == NULL) {
        return NULL;
    }

    j = 0;

    for (i = 0; i < length; i++) {

        if (s[i] != ' ') {
            result[j] = s[i];
            j++;
        }
    }

    result[j] = '\0';

    return result;
}


/* =========================================================
   KEEP ONLY DIGITS
   ========================================================= */

char *string_keep_digits(const char *s)
{
    char *result;
    int length;
    int count;
    int i;
    int j;

    if (s == NULL) {
        return NULL;
    }

    length = 0;
    count = 0;

    while (s[length] != '\0') {

        if (isdigit((unsigned char)s[length])) {
            count++;
        }

        length++;
    }

    result = malloc((count + 1) * sizeof(char));

    if (result == NULL) {
        return NULL;
    }

    j = 0;

    for (i = 0; i < length; i++) {

        if (isdigit((unsigned char)s[i])) {
            result[j] = s[i];
            j++;
        }
    }

    result[j] = '\0';

    return result;
}


/* =========================================================
   REVERSE STRING IN PLACE
   ========================================================= */

void string_reverse_inplace(char *s)
{
    char *left;
    char *right;
    char tmp;

    if (s == NULL || *s == '\0') {
        return;
    }

    left = s;
    right = s;

    while (*right != '\0') {
        right++;
    }

    right--;

    while (left < right) {

        tmp = *left;
        *left = *right;
        *right = tmp;

        left++;
        right--;
    }
}


/* =========================================================
   COUNT WHITESPACE CHARACTERS
   ========================================================= */

int string_count_spaces(const char *s)
{
    int count;

    if (s == NULL) {
        return 0;
    }

    count = 0;

    while (*s != '\0') {

        if (isspace((unsigned char)*s)) {
            count++;
        }

        s++;
    }

    return count;
}


/* =========================================================
   CREATE ARRAY OF STRING POINTERS

   Initially:
   [NULL, NULL, NULL, ...]
   ========================================================= */

char **strings_create(int n)
{
    char **strings;
    int i;

    if (n <= 0) {
        return NULL;
    }

    strings = malloc(n * sizeof(char *));

    if (strings == NULL) {
        return NULL;
    }

    for (i = 0; i < n; i++) {
        strings[i] = NULL;
    }

    return strings;
}


/* =========================================================
   CREATE N FIXED-CAPACITY STRINGS

   Each string can contain up to len characters
   plus the '\0'.
   ========================================================= */

char **strings_create_fixed(int n, int len)
{
    char **strings;
    int i;
    int j;

    if (n <= 0 || len < 0) {
        return NULL;
    }

    strings = malloc(n * sizeof(char *));

    if (strings == NULL) {
        return NULL;
    }

    for (i = 0; i < n; i++) {

        strings[i] = malloc((len + 1) * sizeof(char));

        if (strings[i] == NULL) {

            while (i > 0) {
                i--;
                free(strings[i]);
            }

            free(strings);

            return NULL;
        }

        for (j = 0; j <= len; j++) {
            strings[i][j] = '\0';
        }
    }

    return strings;
}


/* =========================================================
   FREE ARRAY OF STRINGS
   ========================================================= */

void strings_free(char **strings, int n)
{
    int i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; i < n; i++) {
        free(strings[i]);
    }

    free(strings);
}