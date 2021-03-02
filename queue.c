#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

// helper functions
/*
 * Create New Node
 * Return false if malloc failed
 * Otherwise return true
 */
static inline bool ele_create(list_ele_t **newh, char *s)
{
    *newh = malloc(sizeof(list_ele_t));
    // return false if malloc failed
    if (*newh == NULL)
        return false;
    // copy string content
    size_t len = strlen(s) +
                 1;  // count in additional space for c string null terminator
    // malloc string space
    (*newh)->value = malloc(len);
    if ((*newh)->value == NULL) {  // when malloc for string failed
        // prevent memory leak on failed memory allocation
        free(*newh);
        return false;
    }
    // copy string content
    strncpy((*newh)->value, s, len);
    // initialize fields
    (*newh)->next = NULL;
    return true;
}

/*
 * Delete a node
 * Passed pointer is advance to next node automatically
 * Passed pointer must not be null nor pointed to NULL
 * Otherwise, the result is not guaranteed
 */
static inline void ele_delete(list_ele_t **del)
{
    free((*del)->value);             // free string
    list_ele_t *tmp = (*del)->next;  // save pointer for next node
    free(*del);
    *del = tmp;
}

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    // when allocation failed return NULL
    if (q == NULL)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    // free iterated through lists
    if (q != NULL) {
        for (list_ele_t *it = q->head; it != NULL;) {
            ele_delete(&it);
        }
    }
    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    // when q is NULL return false
    if (q == NULL)
        return false;
    // handle node creation failed
    if (!ele_create(&newh, s)) {
        return false;
    }
    newh->next = q->head;
    q->head = newh;
    // correctly initialize tail when is NULL
    if (q->tail == NULL)
        q->tail = q->head;
    // maintain size
    ++(q->size);
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newh;
    // when q is NULL return false
    if (q == NULL)
        return false;
    // if create node fail, return false
    if (!ele_create(&newh, s)) {
        return false;
    }
    // concat to existed list
    // prevent empty list
    if (q->tail != NULL) {
        // concat node to current list
        q->tail->next = newh;
    } else {  // is the first element in list
        q->head = newh;
    }
    // set tail to new node
    q->tail = newh;
    // maintain size
    ++(q->size);
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->head == NULL)
        return false;
    list_ele_t *tmp = q->head;
    // copy string
    if (bufsize > 0 && sp != NULL) {
        strncpy(sp, tmp->value, bufsize);
        sp[bufsize - 1] = 0;  // add possible missing terminator
    }
    // maintain tail record if needed
    if (q->tail == tmp) {
        q->tail = NULL;
    }
    // advance head record
    q->head = tmp->next;
    --(q->size);
    ele_delete(&tmp);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    // let the q_size do the null check
    if (q_size(q) <= 1)
        return;
    list_ele_t *prev = NULL, *tail = q->tail;
    q->tail = q->head;
    for (list_ele_t *it = q->head; it != NULL;) {
        // forward iterator temp
        list_ele_t *tmp = it->next;
        // reverse linkage
        it->next = prev;
        prev = it;  // advance prev
        it = tmp;   // advance iterator
    }
    q->head = tail;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    // PLAN: Use Merge sort implementation
}
