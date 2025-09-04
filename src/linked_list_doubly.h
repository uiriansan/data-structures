#ifndef DS_LL_DOUBLY_H_
#define DS_LL_DOUBLY_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DS_LL_DoublyNode DS_LL_DoublyNode;
typedef struct DS_LL_DoublyList DS_LL_DoublyList;
typedef struct DS_LL_DoublyArray DS_LL_DoublyArray;
static inline DS_LL_DoublyList *ds_ll_doubly_create();
static inline size_t ds_ll_doubly_free(DS_LL_DoublyList *list);
static inline size_t ds_ll_doubly_insert_front(DS_LL_DoublyList *list, char *data);
static inline size_t ds_ll_doubly_append(DS_LL_DoublyList *list, char *data);
static inline void ds_ll_doubly_print(DS_LL_DoublyList *list);
static inline size_t ds_ll_doubly_remove(DS_LL_DoublyList *list, DS_LL_DoublyNode *node);

#ifdef __cplusplus
}
#endif

#ifdef DS_LL_DOUBLY_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DS_LL_DoublyNode {
    char *data;
    DS_LL_DoublyNode *next;
    DS_LL_DoublyNode *prev;
};

struct DS_LL_DoublyList {
    DS_LL_DoublyNode *head;
    DS_LL_DoublyNode *tail;
    size_t size;
};

static inline DS_LL_DoublyList *ds_ll_doubly_create() {
    DS_LL_DoublyList *p = (DS_LL_DoublyList *)malloc(sizeof(DS_LL_DoublyList));
    if (p == NULL)
        return NULL;

    p->head = NULL;
    p->tail = NULL;
    p->size = 0;
    return p;
}

static inline size_t ds_ll_doubly_free(DS_LL_DoublyList *list) {
    if (list == NULL)
        return 0;

    DS_LL_DoublyNode *p = list->head, *tmp;
    size_t i = 0;
    while (p != NULL) {
        tmp = p->next;

        free(p->data);
        free(p);
        p = tmp;

        i++;
    }
    free(list);

    return i;
}

static inline size_t ds_ll_doubly_insert_front(DS_LL_DoublyList *list, char *data) {
    if (list == NULL)
        return 0;

    if (data == NULL)
        return list->size;

    DS_LL_DoublyNode *p = (DS_LL_DoublyNode *)malloc(sizeof(DS_LL_DoublyNode));
    if (p == NULL)
        return list->size;

    p->data = strdup(data);

    if (list->head == NULL) {
        p->next = NULL;
        p->prev = NULL;
        list->head = p;
        list->tail = list->head;
        list->size++;
    } else {
        p->next = list->head;
        p->prev = NULL;
        list->head->prev = p;
        list->head = p;
        list->size++;
    }
    return list->size;
}

static inline size_t ds_ll_doubly_append(DS_LL_DoublyList *list, char *data) {
    if (list == NULL)
        return 0;

    if (data == NULL)
        return list->size;

    DS_LL_DoublyNode *p = (DS_LL_DoublyNode *)malloc(sizeof(DS_LL_DoublyNode));
    if (p == NULL)
        return list->size;

    p->data = strdup(data);

    if (list->head == NULL) {
        p->next = NULL;
        p->prev = NULL;
        list->head = p;
        list->tail = list->head;
        list->size++;
    } else {
        p->next = NULL;
        p->prev = list->tail;
        list->tail->next = p;
        list->tail = p;
        list->size++;
    }
    return list->size;
}

static inline void ds_ll_doubly_print(DS_LL_DoublyList *list) {
    if (list == NULL)
        return;

    DS_LL_DoublyNode *p = list->head;

    while (p != NULL) {
        if (p == list->head)
            printf("NULL <- ");

        printf("%s %s-> ", p->data, p != list->tail ? "<" : "");

        p = p->next;
    }
    printf("NULL\n");
}

static inline size_t ds_ll_doubly_remove(DS_LL_DoublyList *list, DS_LL_DoublyNode *node) {
    if (list == NULL)
        return 0;

    if (node == NULL)
        return list->size;

    if (node == list->head) {
        list->head = list->head->next;
        list->head->prev = NULL;
    } else if (node == list->tail) {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    free(node->data);
    free(node);
    return --list->size;
}

#endif // DS_LL_DOUBLY_IMPLEMENTATION
#endif // DS_LL_DOUBLY_H_
