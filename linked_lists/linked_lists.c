#ifndef ALGORITHMS_DATA_STRUCTURES_C_LINKED_LISTS_H
#define ALGORITHMS_DATA_STRUCTURES_C_LINKED_LISTS_H
#include <stdlib.h>

typedef struct node_s {
    int data;
    struct node_s *next;
} node_t;

/* Basic operations */
int list_count(node_t *head);
int list_sum(node_t *head);
int list_count_value(node_t *head, int x);
node_t *list_search_last(node_t *head, int x);

/* Insertion */
node_t *list_insert_head(node_t *head, int x);
node_t *list_insert_tail(node_t *head, int x);

/* Deletion */
node_t *list_delete_first(node_t *head, int x);
node_t *list_delete_last(node_t *head, int x);
node_t *list_delete_all(node_t *head, int x);

/* Other operations */
node_t *list_reverse(node_t *head);


#endif

#include "linked_lists.h"
#include <stdlib.h>

int list_count(node_t *head)
{
    node_t *cur;
    int cnt;

    cur = head;
    cnt = 0;

    while (cur != NULL) {
        cnt++;
        cur = cur->next;
    }

    return cnt;
}


int list_sum(node_t *head)
{
    node_t *cur;
    int sum;

    cur = head;
    sum = 0;

    while (cur != NULL) {
        sum += cur->data;
        cur = cur->next;
    }

    return sum;
}



node_t *list_insert_head(node_t *head, int x)
{
    node_t *new_node;

    new_node = malloc(sizeof(node_t));

    if (new_node == NULL)
        return head;

    new_node->data = x;
    new_node->next = head;

    return new_node;
}


node_t *list_insert_tail(node_t *head, int x)
{
    node_t *new_node;
    node_t *cur;

    new_node = malloc(sizeof(node_t));

    if (new_node == NULL)
        return head;

    new_node->data = x;
    new_node->next = NULL;

    if (head == NULL)
        return new_node;

    cur = head;

    while (cur->next != NULL) {
        cur = cur->next;
    }

    cur->next = new_node;

    return head;
}



node_t *list_delete_last(node_t *head, int x)
{
    node_t *cur;
    node_t *pre;
    node_t *last;
    node_t *last_pre;

    cur = head;
    pre = NULL;
    last = NULL;
    last_pre = NULL;

    while (cur != NULL) {

        if (cur->data == x) {
            last = cur;
            last_pre = pre;
        }

        pre = cur;
        cur = cur->next;
    }

    if (last == NULL)
        return head;

    if (last_pre == NULL)
        head = last->next;
    else
        last_pre->next = last->next;

    free(last);

    return head;
}




node_t *list_reverse(node_t *head)
{
    node_t *pre;
    node_t *cur;
    node_t *next;

    pre = NULL;
    cur = head;

    while (cur != NULL) {
        next = cur->next;
        cur->next = pre;

        pre = cur;
        cur = next;
    }

    return pre;
}


node_t *list_merge(node_t *head1, node_t *head2)
{
    node_t *head;
    node_t *tail;
    node_t *p;

    head = NULL;
    tail = NULL;

    while (head1 != NULL && head2 != NULL) {

        if (head1->data <= head2->data) {
            p = head1;
            head1 = head1->next;
        } else {
            p = head2;
            head2 = head2->next;
        }

        p->next = NULL;

        if (head == NULL) {
            head = p;
            tail = p;
        } else {
            tail->next = p;
            tail = p;
        }
    }

    if (head1 != NULL) {
        p = head1;
    } else {
        p = head2;
    }

    if (head == NULL) {
        head = p;
    } else {
        tail->next = p;
    }

    return head;
}


node_t *list_partition(node_t *head, int x)
{
    node_t *less_head;
    node_t *less_tail;
    node_t *greater_head;
    node_t *greater_tail;
    node_t *cur;
    node_t *next;

    less_head = NULL;
    less_tail = NULL;
    greater_head = NULL;
    greater_tail = NULL;

    cur = head;

    while (cur != NULL) {

        next = cur->next;
        cur->next = NULL;

        if (cur->data < x) {

            if (less_head == NULL) {
                less_head = cur;
                less_tail = cur;
            } else {
                less_tail->next = cur;
                less_tail = cur;
            }

        } else {

            if (greater_head == NULL) {
                greater_head = cur;
                greater_tail = cur;
            } else {
                greater_tail->next = cur;
                greater_tail = cur;
            }
        }

        cur = next;
    }

    if (less_head == NULL) {
        return greater_head;
    }

    less_tail->next = greater_head;

    return less_head;
}

node_t *list_extract(node_t **head, int value)
{
    node_t *cur;
    node_t *pre;
    node_t *tmp;

    if (head == NULL || *head == NULL) {
        return NULL;
    }

    if ((*head)->data == value) {
        tmp = *head;
        *head = (*head)->next;
        tmp->next = NULL;

        return tmp;
    }

    pre = *head;
    cur = (*head)->next;

    while (cur != NULL && cur->data != value) {
        pre = cur;
        cur = cur->next;
    }

    if (cur == NULL) {
        return NULL;
    }

    pre->next = cur->next;
    cur->next = NULL;

    return cur;
}

node_t *list_intersection(node_t **head1, node_t **head2) {

    node_t *p1;
    node_t *p2;
    node_t *pre1;
    node_t *pre2;
    node_t *next1;
    node_t *next2;
    node_t *result;
    node_t *tail;

    p1 = *head1;
    p2 = *head2;

    pre1 = NULL;
    pre2 = NULL;

    result = NULL;
    tail = NULL;

    while (p1 != NULL && p2 != NULL) {

        if (p1->data < p2->data) {
            pre1 = p1;
            p1 = p1->next;

        } else if (p1->data > p2->data) {
            pre2 = p2;
            p2 = p2->next;

        } else {

            next1 = p1->next;
            next2 = p2->next;

            if (pre1 == NULL) {
                *head1 = next1;
            } else {
                pre1->next = next1;
            }

            if (pre2 == NULL) {
                *head2 = next2;
            } else {
                pre2->next = next2;
            }

            p1->next = NULL;

            if (result == NULL) {
                result = p1;
                tail = p1;
            } else {
                tail->next = p1;
                tail = p1;
            }

            free(p2);

            p1 = next1;
            p2 = next2;
        }
    }

    return result;
}
void list_free(node_t *head)
{
    node_t *next;

    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    }
}

node_t *list_search(node_t *head, int value)
{
    node_t *cur;

    cur = head;

    while (cur != NULL && cur->data != value) {
        cur = cur->next;
    }

    return cur;
}


node_t *list_last(node_t *head)
{
    node_t *cur;

    if (head == NULL) {
        return NULL;
    }

    cur = head;

    while (cur->next != NULL) {
        cur = cur->next;
    }

    return cur;
}


int list_count_value(node_t *head, int value)
{
    node_t *cur;
    int count;

    count = 0;
    cur = head;

    while (cur != NULL) {
        if (cur->data == value) {
            count++;
        }

        cur = cur->next;
    }

    return count;
}


node_t *list_search_last(node_t *head, int value)
{
    node_t *cur;
    node_t *last;

    cur = head;
    last = NULL;

    while (cur != NULL) {
        if (cur->data == value) {
            last = cur;
        }

        cur = cur->next;
    }

    return last;
}


node_t *list_delete_first(node_t *head, int value)
{
    node_t *cur;
    node_t *pre;

    if (head == NULL) {
        return NULL;
    }

    if (head->data == value) {
        cur = head;
        head = head->next;
        free(cur);

        return head;
    }

    pre = head;
    cur = head->next;

    while (cur != NULL && cur->data != value) {
        pre = cur;
        cur = cur->next;
    }

    if (cur == NULL) {
        return head;
    }

    pre->next = cur->next;
    free(cur);

    return head;
}


node_t *list_delete_all(node_t *head, int value)
{
    node_t *cur;
    node_t *pre;
    node_t *tmp;

    while (head != NULL && head->data == value) {
        tmp = head;
        head = head->next;
        free(tmp);
    }

    if (head == NULL) {
        return NULL;
    }

    pre = head;
    cur = head->next;

    while (cur != NULL) {

        if (cur->data == value) {
            tmp = cur;
            pre->next = cur->next;
            cur = cur->next;
            free(tmp);
        } else {
            pre = cur;
            cur = cur->next;
        }
    }

    return head;
}
node_t *list_duplicate(node_t *head)
{
    node_t *cur;
    node_t *new_node;
    node_t *new_head;
    node_t *tail;

    cur = head;
    new_head = NULL;
    tail = NULL;

    while (cur != NULL) {

        new_node = malloc(sizeof(node_t));

        if (new_node == NULL) {
            list_free(new_head);
            return NULL;
        }

        new_node->data = cur->data;
        new_node->next = NULL;

        if (new_head == NULL) {
            new_head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }

        cur = cur->next;
    }

    return new_head;
}


node_t *list_duplicate_reverse(node_t *head)
{
    node_t *cur;
    node_t *new_node;
    node_t *new_head;

    cur = head;
    new_head = NULL;

    while (cur != NULL) {

        new_node = malloc(sizeof(node_t));

        if (new_node == NULL) {
            list_free(new_head);
            return NULL;
        }

        new_node->data = cur->data;
        new_node->next = new_head;

        new_head = new_node;
        cur = cur->next;
    }

    return new_head;
}


node_t *list_split_at_duplicate(node_t *head)
{
    node_t *cur;
    node_t *p;
    node_t *pre;

    if (head == NULL) {
        return NULL;
    }

    pre = NULL;
    cur = head;

    while (cur != NULL) {

        p = head;

        while (p != cur && p->data != cur->data) {
            p = p->next;
        }

        if (p != cur) {
            pre->next = NULL;
            return cur;
        }

        pre = cur;
        cur = cur->next;
    }

    return NULL;
}

node_t *list_shared_node(node_t *head1, node_t *head2)
{
    node_t *p1;
    node_t *p2;

    p1 = head1;

    while (p1 != NULL) {

        p2 = head2;

        while (p2 != NULL) {

            if (p1 == p2) {
                return p1;
            }

            p2 = p2->next;
        }

        p1 = p1->next;
    }

    return NULL;
}