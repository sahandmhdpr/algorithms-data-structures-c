#include "trees.h"

#include <stdio.h>
#include <stdlib.h>


tree_node_t *bst_search(tree_node_t *root, int value)
{
    if (root == NULL) {
        return NULL;
    }

    if (value < root->data) {
        return bst_search(root->left, value);
    }

    if (value > root->data) {
        return bst_search(root->right, value);
    }

    return root;
}


tree_node_t *bst_insert(tree_node_t *root, int value)
{
    tree_node_t *new_node;

    if (root == NULL) {

        new_node = malloc(sizeof(tree_node_t));

        if (new_node == NULL) {
            return NULL;
        }

        new_node->data = value;
        new_node->left = NULL;
        new_node->right = NULL;

        return new_node;
    }

    if (value < root->data) {
        root->left = bst_insert(root->left, value);
    } else if (value > root->data) {
        root->right = bst_insert(root->right, value);
    }

    return root;
}


tree_node_t *bst_min(tree_node_t *root)
{
    if (root == NULL) {
        return NULL;
    }

    while (root->left != NULL) {
        root = root->left;
    }

    return root;
}


tree_node_t *bst_max(tree_node_t *root)
{
    if (root == NULL) {
        return NULL;
    }

    while (root->right != NULL) {
        root = root->right;
    }

    return root;
}


tree_node_t *bst_delete(tree_node_t *root, int value)
{
    tree_node_t *tmp;

    if (root == NULL) {
        return NULL;
    }

    if (value < root->data) {

        root->left = bst_delete(root->left, value);

    } else if (value > root->data) {

        root->right = bst_delete(root->right, value);

    } else {

        /* No children */
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        /* Only right child */
        if (root->left == NULL) {
            tmp = root->right;
            free(root);
            return tmp;
        }

        /* Only left child */
        if (root->right == NULL) {
            tmp = root->left;
            free(root);
            return tmp;
        }

        /*
         * Two children:
         * use inorder successor = minimum of right subtree.
         */
        tmp = bst_min(root->right);

        root->data = tmp->data;

        root->right = bst_delete(root->right, tmp->data);
    }

    return root;
}


int bst_height(tree_node_t *root)
{
    int left_height;
    int right_height;

    if (root == NULL) {
        return 0;
    }

    left_height = bst_height(root->left);
    right_height = bst_height(root->right);

    if (left_height > right_height) {
        return left_height + 1;
    }

    return right_height + 1;
}


int bst_count(tree_node_t *root)
{
    if (root == NULL) {
        return 0;
    }

    return 1
           + bst_count(root->left)
           + bst_count(root->right);
}


int bst_count_leaves(tree_node_t *root)
{
    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return 1;
    }

    return bst_count_leaves(root->left)
           + bst_count_leaves(root->right);
}


int bst_count_internal(tree_node_t *root)
{
    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return 0;
    }

    return 1
           + bst_count_internal(root->left)
           + bst_count_internal(root->right);
}


int bst_count_single_child(tree_node_t *root)
{
    int current;

    if (root == NULL) {
        return 0;
    }

    current = 0;

    if ((root->left != NULL && root->right == NULL) ||
        (root->left == NULL && root->right != NULL)) {

        current = 1;
    }

    return current
           + bst_count_single_child(root->left)
           + bst_count_single_child(root->right);
}


int bst_count_two_children(tree_node_t *root)
{
    int current;

    if (root == NULL) {
        return 0;
    }

    current = 0;

    if (root->left != NULL && root->right != NULL) {
        current = 1;
    }

    return current
           + bst_count_two_children(root->left)
           + bst_count_two_children(root->right);
}


int bst_sum(tree_node_t *root)
{
    if (root == NULL) {
        return 0;
    }

    return root->data
           + bst_sum(root->left)
           + bst_sum(root->right);
}


int bst_sum_leaves(tree_node_t *root)
{
    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return root->data;
    }

    return bst_sum_leaves(root->left)
           + bst_sum_leaves(root->right);
}


int bst_count_even(tree_node_t *root)
{
    int current;

    if (root == NULL) {
        return 0;
    }

    current = 0;

    if (root->data % 2 == 0) {
        current = 1;
    }

    return current
           + bst_count_even(root->left)
           + bst_count_even(root->right);
}


int bst_count_negative(tree_node_t *root)
{
    int current;

    if (root == NULL) {
        return 0;
    }

    current = 0;

    if (root->data < 0) {
        current = 1;
    }

    return current
           + bst_count_negative(root->left)
           + bst_count_negative(root->right);
}


int bst_count_level(tree_node_t *root, int level)
{
    if (root == NULL || level < 0) {
        return 0;
    }

    if (level == 0) {
        return 1;
    }

    return bst_count_level(root->left, level - 1)
           + bst_count_level(root->right, level - 1);
}


int bst_sum_level(tree_node_t *root, int level)
{
    if (root == NULL || level < 0) {
        return 0;
    }

    if (level == 0) {
        return root->data;
    }

    return bst_sum_level(root->left, level - 1)
           + bst_sum_level(root->right, level - 1);
}


int bst_count_greater_level(tree_node_t *root,
                            int value,
                            int level)
{
    if (root == NULL || level < 0) {
        return 0;
    }

    if (level == 0) {
        return root->data > value;
    }

    return bst_count_greater_level(root->left,
                                   value,
                                   level - 1)
           +
           bst_count_greater_level(root->right,
                                   value,
                                   level - 1);
}


int bst_count_greater(tree_node_t *root, int value)
{
    if (root == NULL) {
        return 0;
    }

    /*
     * Since this is a BST, if root <= value,
     * the entire left subtree can be skipped.
     */
    if (root->data <= value) {
        return bst_count_greater(root->right, value);
    }

    return 1
           + bst_count(root->right)
           + bst_count_greater(root->left, value);
}


int bst_count_range(tree_node_t *root, int min, int max)
{
    if (root == NULL || min > max) {
        return 0;
    }

    /*
     * BST pruning:
     * values in the left subtree are smaller,
     * values in the right subtree are larger.
     */

    if (root->data < min) {
        return bst_count_range(root->right, min, max);
    }

    if (root->data > max) {
        return bst_count_range(root->left, min, max);
    }

    return 1
           + bst_count_range(root->left, min, max)
           + bst_count_range(root->right, min, max);
}


int bst_is_leaf(tree_node_t *root)
{
    if (root == NULL) {
        return 0;
    }

    return root->left == NULL && root->right == NULL;
}


int bst_same_shape(tree_node_t *root1, tree_node_t *root2)
{
    if (root1 == NULL && root2 == NULL) {
        return 1;
    }

    if (root1 == NULL || root2 == NULL) {
        return 0;
    }

    return bst_same_shape(root1->left, root2->left)
           &&
           bst_same_shape(root1->right, root2->right);
}


void bst_inorder(tree_node_t *root)
{
    if (root == NULL) {
        return;
    }

    bst_inorder(root->left);

    printf("%d ", root->data);

    bst_inorder(root->right);
}


void bst_preorder(tree_node_t *root)
{
    if (root == NULL) {
        return;
    }

    printf("%d ", root->data);

    bst_preorder(root->left);

    bst_preorder(root->right);
}


void bst_postorder(tree_node_t *root)
{
    if (root == NULL) {
        return;
    }

    bst_postorder(root->left);

    bst_postorder(root->right);

    printf("%d ", root->data);
}


void bst_free(tree_node_t *root)
{
    if (root == NULL) {
        return;
    }

    bst_free(root->left);
    bst_free(root->right);

    free(root);
}