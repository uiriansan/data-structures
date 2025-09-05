#ifndef DS_Q_H_
#define DS_Q_H_

#include <stddef.h>
#define DS_LL_DOUBLY_IMPLEMENTATION
#include "linked_list_doubly.h"

#ifdef __cplusplus
extern "C" {
#endif

// A queue is a FIFO data structure (First In, First Out).
// New elements are added to the end of the list and the old elements are removed from the front.
typedef struct DS_Queue DS_Queue;
// Create a queue.
static inline DS_Queue *ds_q_create();
// Free a queue and all its data.
static inline size_t ds_q_free(DS_Queue *queue);
// Add an element to the end of the queue.
static inline void ds_q_enqueue(DS_Queue *queue, char *data);
// Get the size of a queue's internal list (not the same as queue->size).
static inline size_t ds_q_get_size(DS_Queue *queue);
// Get the data of the element at the front of the queue and remove it from the list.
// This operation returns a `char *` that must be manually freed using `free()`.
static inline char *ds_q_dequeue(DS_Queue *queue);
// Get the data of the element at the front of the queue without removing it from the list.
// This operation returns a `char *` that must be manually freed using `free()`.
static inline char *ds_q_peek(DS_Queue *queue);
// Print the queue.
static inline void ds_q_print(DS_Queue *queue);

#ifdef __cplusplus
}
#endif

#ifdef DS_Q_IMPLEMENTATION
struct DS_Queue {
    DS_LL_DoublyNode *head;
    DS_LL_DoublyNode *tail;
    size_t size;
};

static inline DS_Queue *ds_q_create() {
    DS_Queue *q = (DS_Queue *)malloc(sizeof(DS_Queue));
    q->head = ds_ll_doubly_create_node(NULL);
    q->tail = NULL;
    q->size = 0;
    return q;
}

static inline size_t ds_q_free(DS_Queue *queue) {
    if (queue == NULL)
        return 0;

    size_t fc = ds_ll_doubly_free(queue->head);
    free(queue);

    return fc;
}

static inline size_t ds_q_get_size(DS_Queue *queue) {
    if (queue == NULL)
        return 0;
    return ds_ll_doubly_get_size(queue->head);
}

static inline void ds_q_enqueue(DS_Queue *queue, char *data) {
    if (queue == NULL || data == NULL)
        return;

    if (queue->head->data == NULL) {
        queue->head->data = strdup(data);
        queue->tail = queue->head;
    } else {
        DS_LL_DoublyNode *tp = ds_ll_doubly_create_node(data);
        if (tp == NULL)
            return;

        tp->prev = queue->tail;
        queue->tail->next = tp;
        queue->tail = tp;
    }
    queue->size++;
}

static inline char *ds_q_dequeue(DS_Queue *queue) {
    if (queue == NULL || queue->head->data == NULL)
        return NULL;

    char *data = (char *)malloc(strlen(queue->head->data));
    strcpy(data, queue->head->data);

    if (queue->head->next == NULL) {
        free(queue->head->data);
        queue->head->data = NULL;
    } else {
        DS_LL_DoublyNode *nh = queue->head->next;
        nh->prev = NULL;
        free(queue->head->data);
        free(queue->head);
        queue->head = nh;
    }
    queue->size--;

    return data;
}

static inline char *ds_q_peek(DS_Queue *queue) {
    if (queue == NULL || queue->head->data == NULL)
        return NULL;

    char *data = (char *)malloc(strlen(queue->head->data));
    strcpy(data, queue->head->data);
    return data;
}

static inline void ds_q_print(DS_Queue *queue) {
    if (queue == NULL || queue->head->data == NULL) {
        printf("The queue is empty.\n");
        return;
    }

    DS_LL_DoublyNode *p = queue->head;
    size_t i = 0;

    printf("Queue:\n");
    while (p != NULL) {
        printf("  %03zu: %s\n", i + 1, p->data);
        p = p->next;
        i++;
    }
}

#endif // DS_Q_IMPLEMENTATION
#endif // DS_Q_H_
