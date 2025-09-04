#ifndef DS_LL_DOUBLY_H_
#define DS_LL_DOUBLY_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DS_LL_DoublyNode DS_LL_DoublyNode;
typedef struct DS_LL_DoublyArray DS_LL_DoublyArray;
static inline DS_LL_DoublyNode *ds_ll_doubly_create_node(char *data);
static inline size_t ds_ll_doubly_free(DS_LL_DoublyNode *head);
static inline size_t ds_ll_doubly_get_size(DS_LL_DoublyNode *head);
static inline DS_LL_DoublyNode *ds_ll_doubly_get_tail(DS_LL_DoublyNode *head);
static inline DS_LL_DoublyNode *ds_ll_doubly_insert_front(DS_LL_DoublyNode **head, char *data);
static inline DS_LL_DoublyNode *ds_ll_doubly_append(DS_LL_DoublyNode *head, char *data);
static inline void ds_ll_doubly_print(DS_LL_DoublyNode *head);
static inline void ds_ll_doubly_remove(DS_LL_DoublyNode **head, DS_LL_DoublyNode *node);

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

static inline DS_LL_DoublyNode *ds_ll_doubly_create_node(char *data) {
    DS_LL_DoublyNode *p = (DS_LL_DoublyNode *)malloc(sizeof(DS_LL_DoublyNode));
    p->data = NULL;
    if (data != NULL)
        p->data = strdup(data);
    p->next = NULL;
    p->prev = NULL;
    return p;
}

static inline size_t ds_ll_doubly_free(DS_LL_DoublyNode *head) {
    if (head == NULL)
        return 0;

    DS_LL_DoublyNode *p = head, *tmp;
    size_t i = 0;

    while (p != NULL) {
        tmp = p->next;

        free(p->data);
        free(p);
        p = tmp;

        i++;
    }

    return i;
}

static inline size_t ds_ll_doubly_get_size(DS_LL_DoublyNode *head) {
    size_t i = 0;
    while (head != NULL && head->data != NULL) {
        head = head->next;
        i++;
    }
    return i;
}

static inline DS_LL_DoublyNode *ds_ll_doubly_get_tail(DS_LL_DoublyNode *head) {
    if (head == NULL)
        return NULL;

    DS_LL_DoublyNode *tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    return tail;
}

static inline DS_LL_DoublyNode *ds_ll_doubly_insert_front(DS_LL_DoublyNode **head, char *data) {
    DS_LL_DoublyNode *hp = *head, *p;

    if (hp->data == NULL) {
        hp->data = strdup(data);
        p = hp;
    } else {
        p = ds_ll_doubly_create_node(data);
        if (p == NULL)
            return NULL;

        p->next = *head;
        p->prev = NULL;
        hp->prev = p;
        *head = p;
    }

    return p;
}

static inline DS_LL_DoublyNode *ds_ll_doubly_append(DS_LL_DoublyNode *head, char *data) {
    DS_LL_DoublyNode *p;

    if (head->data == NULL) {
        head->data = strdup(data);
        p = head;
    } else {
        p = ds_ll_doubly_create_node(data);
        if (p == NULL)
            return NULL;

        p->next = NULL;
        DS_LL_DoublyNode *tail = ds_ll_doubly_get_tail(head);
        p->prev = tail;
        tail->next = p;
    }

    return p;
}

static inline void ds_ll_doubly_print(DS_LL_DoublyNode *head) {
    printf("NULL <- ");
    while (head != NULL) {
        printf("%s %s-> ", head->data ? head->data : "(null)", head->next != NULL ? "<" : "");
        head = head->next;
    }
    printf("NULL\n");
}

static inline void ds_ll_doubly_remove(DS_LL_DoublyNode **head, DS_LL_DoublyNode *node) {
    if (node == NULL)
        return;

    DS_LL_DoublyNode *p = *head, *tail = ds_ll_doubly_get_tail(p);

    if (node == p) {
        if (p->next != NULL) {
            *head = p->next;
            p->prev = NULL;
        } else {
            free(node->data);
            p->data = NULL;
            return;
        }
    } else if (node == tail) {
        if (tail->prev != NULL) {
            tail = tail->prev;
            tail->next = NULL;
        } else {
            free(node->data);
            tail->data = NULL;
            return;
        }
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        free(node->data);
    }
    free(node);
}

#endif // DS_LL_DOUBLY_IMPLEMENTATION
#endif // DS_LL_DOUBLY_H_
