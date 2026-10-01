#ifndef ALGORITHMS_DATA_STRUCTURES_C_LINKED_LISTS_H
#define ALGORITHMS_DATA_STRUCTURES_C_LINKED_LISTS_H

typedef struct node_s {
    int data;
    struct node_s *next;
} node_t;

/* Basic operations */
int list_count(node_t *head);
int list_sum(node_t *head);
node_t *list_search(node_t *head, int value);
node_t *list_last(node_t *head);
int list_count_value(node_t *head, int value);
node_t *list_search_last(node_t *head, int value);

/* Insertion */
node_t *list_insert_head(node_t *head, int value);
node_t *list_insert_tail(node_t *head, int value);

/* Deletion */
node_t *list_delete_first(node_t *head, int value);
node_t *list_delete_last(node_t *head, int value);
node_t *list_delete_all(node_t *head, int value);

/* Transformations */
node_t *list_reverse(node_t *head);
node_t *list_merge(node_t *head1, node_t *head2);
node_t *list_partition(node_t *head, int value);

/* Extraction and intersection */
node_t *list_extract(node_t **head, int value);
node_t *list_intersection(node_t **head1, node_t **head2);

/* Duplication and splitting */
node_t *list_duplicate(node_t *head);
node_t *list_duplicate_reverse(node_t *head);
node_t *list_split_at_duplicate(node_t *head);
node_t *list_shared_node(node_t *head1, node_t *head2);
node_t *list_shared_node(node_t *head1, node_t *head2);

/* Memory management */
void list_free(node_t *head);

#endif