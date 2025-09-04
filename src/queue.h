#ifndef DS_Q_H_
#define DS_Q_H_

#include <stddef.h>
#define DS_LL_DOUBLY_IMPLEMENTATION
#include "linked_list_doubly.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DS_Queue DS_Queue;
static inline DS_Queue *ds_q_create();
static inline size_t ds_q_free(DS_Queue *queue);
static inline void ds_q_enqueue(DS_Queue *queue, char *data);
static inline size_t ds_q_get_size(DS_Queue *queue);
static inline char *ds_q_dequeue(DS_Queue *queue);
static inline char *peek(DS_Queue *queue);

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
