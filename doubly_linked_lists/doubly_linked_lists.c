#include "doubly_linked_lists.h"
#include <stdlib.h>


int dll_count(dnode_t *head)
{
    dnode_t *cur;
    int count;

    count = 0;
    cur = head;

    while (cur != NULL) {
        count++;
        cur = cur->next;
    }

    return count;
}


dnode_t *dll_search(dnode_t *head, int value)
{
    dnode_t *cur;

    cur = head;

    while (cur != NULL && cur->data != value) {
        cur = cur->next;
    }

    return cur;
}


dnode_t *dll_last(dnode_t *head)
{
    dnode_t *cur;

    if (head == NULL) {
        return NULL;
    }

    cur = head;

    while (cur->next != NULL) {
        cur = cur->next;
    }

    return cur;
}


dnode_t *dll_insert_head(dnode_t *head, int value)
{
    dnode_t *new_node;

    new_node = malloc(sizeof(dnode_t));

    if (new_node == NULL) {
        return head;
    }

    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = head;

    if (head != NULL) {
        head->prev = new_node;
    }

    return new_node;
}


dnode_t *dll_insert_tail(dnode_t *head, int value)
{
    dnode_t *new_node;
    dnode_t *tail;

    new_node = malloc(sizeof(dnode_t));

    if (new_node == NULL) {
        return head;
    }

    new_node->data = value;
    new_node->next = NULL;

    if (head == NULL) {
        new_node->prev = NULL;
        return new_node;
    }

    tail = dll_last(head);

    new_node->prev = tail;
    tail->next = new_node;

    return head;
}


/*
 * Inserts an already existing node immediately after pred.
 *
 * This is the arbitrary DLL insertion pattern from the
 * original Algorithms & Programming exercises.
 */
void dll_insert_after(dnode_t *pred, dnode_t *node)
{
    if (pred == NULL || node == NULL) {
        return;
    }

    node->prev = pred;
    node->next = pred->next;

    if (pred->next != NULL) {
        pred->next->prev = node;
    }

    pred->next = node;
}


dnode_t *dll_delete_first(dnode_t *head, int value)
{
    dnode_t *cur;

    cur = head;

    while (cur != NULL && cur->data != value) {
        cur = cur->next;
    }

    if (cur == NULL) {
        return head;
    }

    if (cur->prev != NULL) {
        cur->prev->next = cur->next;
    } else {
        head = cur->next;
    }

    if (cur->next != NULL) {
        cur->next->prev = cur->prev;
    }

    free(cur);

    return head;
}


dnode_t *dll_middle(dnode_t *head)
{
    dnode_t *slow;
    dnode_t *fast;

    if (head == NULL) {
        return NULL;
    }

    slow = head;
    fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}


dnode_t *dll_reverse(dnode_t *head)
{
    dnode_t *cur;
    dnode_t *tmp;

    cur = head;

    while (cur != NULL) {

        tmp = cur->prev;
        cur->prev = cur->next;
        cur->next = tmp;

        head = cur;
        cur = cur->prev;
    }

    return head;
}


void dll_free(dnode_t *head)
{
    dnode_t *next;

    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    }
}