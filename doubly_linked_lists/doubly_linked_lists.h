#ifndef ALGORITHMS_DATA_STRUCTURES_C_DOUBLY_LINKED_LISTS_H
#define ALGORITHMS_DATA_STRUCTURES_C_DOUBLY_LINKED_LISTS_H

typedef struct dnode_s {
    int data;
    struct dnode_s *prev;
    struct dnode_s *next;
} dnode_t;

/* Basic operations */
int dll_count(dnode_t *head);
dnode_t *dll_search(dnode_t *head, int value);
dnode_t *dll_last(dnode_t *head);

/* Insertion */
dnode_t *dll_insert_head(dnode_t *head, int value);
dnode_t *dll_insert_tail(dnode_t *head, int value);
void dll_insert_after(dnode_t *pred, dnode_t *node);

/* Deletion */
dnode_t *dll_delete_first(dnode_t *head, int value);

/* Algorithms */
dnode_t *dll_middle(dnode_t *head);
dnode_t *dll_reverse(dnode_t *head);

/* Memory management */
void dll_free(dnode_t *head);

#endif