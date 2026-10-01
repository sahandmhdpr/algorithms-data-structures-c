#ifndef ALGORITHMS_DATA_STRUCTURES_C_TREES_H
#define ALGORITHMS_DATA_STRUCTURES_C_TREES_H

typedef struct tree_node_s {
    int data;
    struct tree_node_s *left;
    struct tree_node_s *right;
} tree_node_t;

/* Search and insertion */
tree_node_t *bst_search(tree_node_t *root, int value);
tree_node_t *bst_insert(tree_node_t *root, int value);

/* Minimum and maximum */
tree_node_t *bst_min(tree_node_t *root);
tree_node_t *bst_max(tree_node_t *root);

/* Deletion */
tree_node_t *bst_delete(tree_node_t *root, int value);

/* Tree properties */
int bst_height(tree_node_t *root);
int bst_count(tree_node_t *root);
int bst_count_leaves(tree_node_t *root);
int bst_count_internal(tree_node_t *root);
int bst_count_single_child(tree_node_t *root);
int bst_count_two_children(tree_node_t *root);

/* Value operations */
int bst_sum(tree_node_t *root);
int bst_sum_leaves(tree_node_t *root);
int bst_count_even(tree_node_t *root);
int bst_count_negative(tree_node_t *root);

/* Level operations */
int bst_count_level(tree_node_t *root, int level);
int bst_sum_level(tree_node_t *root, int level);
int bst_count_greater_level(tree_node_t *root, int value, int level);

/* Queries */
int bst_count_greater(tree_node_t *root, int value);
int bst_count_range(tree_node_t *root, int min, int max);

/* Structural operations */
int bst_is_leaf(tree_node_t *root);
int bst_same_shape(tree_node_t *root1, tree_node_t *root2);

/* Traversals */
void bst_inorder(tree_node_t *root);
void bst_preorder(tree_node_t *root);
void bst_postorder(tree_node_t *root);

/* Memory */
void bst_free(tree_node_t *root);

#endif