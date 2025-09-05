
#ifndef DS_DQ_H_
#define DS_DQ_H_

#include <stddef.h>
#define DS_LL_DOUBLY_IMPLEMENTATION
#include "linked_list_doubly.h"

#ifdef __cplusplus
extern "C" {
#endif

// A deque (double-ended queue) is a type of queue for which its elements
// can be added or removed from either the front or the back of the list.
typedef struct DS_Deque DS_Deque;
// Create a deque.
static inline DS_Deque *ds_dq_create();
// Free a deque and all its data.
static inline size_t ds_dq_free(DS_Deque *deque);
// Returns the size of a deque's internal list (not the same as deque->size).
static inline size_t ds_dq_get_size(DS_Deque *deque);
// Add an element to the front of the deque.
static inline void ds_dq_push_front(DS_Deque *deque, char *data);
// Add an element to the back of the deque.
static inline void ds_dq_push_back(DS_Deque *deque, char *data);
// Gets the element at the front of the deque and removes it from the list.
static inline char *ds_dq_pop_front(DS_Deque *deque);
// Gets the element at the back of the deque and removes it from the list.
static inline char *ds_dq_pop_back(DS_Deque *deque);
// Print the deque.
static inline void ds_dq_print(DS_Deque *deque);

#ifdef __cplusplus
}
#endif

#ifdef DS_DQ_IMPLEMENTATION
struct DS_Deque {
    DS_LL_DoublyNode *head;
    DS_LL_DoublyNode *tail;
    size_t size;
};

static inline DS_Deque *ds_dq_create() {
    DS_Deque *q = (DS_Deque *)malloc(sizeof(DS_Deque));
    q->head = ds_ll_doubly_create_node(NULL);
    q->tail = NULL;
    q->size = 0;
    return q;
}

static inline size_t ds_dq_free(DS_Deque *deque) {
    if (deque == NULL)
        return 0;

    size_t fc = ds_ll_doubly_free(deque->head);
    free(deque);

    return fc;
}

static inline size_t ds_dq_get_size(DS_Deque *deque) {
    if (deque == NULL)
        return 0;
    return ds_ll_doubly_get_size(deque->head);
}

static inline void ds_dq_push_back(DS_Deque *deque, char *data) {
    if (deque == NULL || data == NULL)
        return;

    if (deque->head->data == NULL) {
        deque->head->data = strdup(data);
        deque->tail = deque->head;
    } else {
        DS_LL_DoublyNode *tp = ds_ll_doubly_create_node(data);
        if (tp == NULL)
            return;

        tp->prev = deque->tail;
        deque->tail->next = tp;
        deque->tail = tp;
    }
    deque->size++;
}

static inline void ds_dq_push_front(DS_Deque *deque, char *data) {
    if (deque == NULL || data == NULL)
        return;

    if (deque->head->data == NULL) {
        deque->head->data = strdup(data);
        deque->tail = deque->head;
    } else {
        DS_LL_DoublyNode *hp = ds_ll_doubly_create_node(data);
        if (hp == NULL)
            return;

        hp->next = deque->head;
        deque->head->prev = hp;
        deque->head = hp;
    }
    deque->size++;
}

static inline char *ds_dq_pop_front(DS_Deque *deque) {
    if (deque == NULL || deque->head->data == NULL)
        return NULL;

    char *data = (char *)malloc(strlen(deque->head->data));
    strcpy(data, deque->head->data);

    if (deque->head->next == NULL) {
        free(deque->head->data);
        deque->head->data = NULL;
    } else {
        DS_LL_DoublyNode *nh = deque->head->next;
        nh->prev = NULL;
        free(deque->head->data);
        free(deque->head);
        deque->head = nh;
    }
    deque->size--;

    return data;
}

static inline char *ds_dq_pop_back(DS_Deque *deque) {
    if (deque == NULL || deque->head->data == NULL)
        return NULL;

    char *data = (char *)malloc(strlen(deque->tail->data));
    strcpy(data, deque->tail->data);

    if (deque->tail->prev == NULL) {
        free(deque->tail->data);
        deque->tail->data = NULL;
    } else {
        DS_LL_DoublyNode *nt = deque->tail->prev;
        nt->next = NULL;
        free(deque->tail->data);
        free(deque->tail);
        deque->tail = nt;
    }
    deque->size--;

    return data;
}

static inline void ds_dq_print(DS_Deque *deque) {
    if (deque == NULL || deque->head->data == NULL) {
        printf("The deque is empty.\n");
        return;
    }

    DS_LL_DoublyNode *p = deque->head;
    size_t i = 0;

    printf("Deque:\n");
    while (p != NULL) {
        printf("  %03zu: %s\n", i + 1, p->data);
        p = p->next;
        i++;
    }
}

#endif // DS_DQ_IMPLEMENTATION
#endif // DS_DQ_H_
