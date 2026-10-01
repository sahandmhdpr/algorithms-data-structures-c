#ifndef ALGORITHMS_DATA_STRUCTURES_C_STRINGS_H
#define ALGORITHMS_DATA_STRUCTURES_C_STRINGS_H


/* Dynamic string operations */
char *string_copy(const char *s);

char *string_concat(const char *s1,
                    const char *s2);

char *string_reverse(const char *s);

char *string_remove_spaces(const char *s);

char *string_keep_digits(const char *s);


/* In-place operation */
void string_reverse_inplace(char *s);


/* String information */
int string_count_spaces(const char *s);


/* Dynamic arrays of strings */
char **strings_create(int n);

char **strings_create_fixed(int n, int len);

void strings_free(char **strings, int n);


#endif