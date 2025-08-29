#ifndef DS_LL_H_
#define DS_LL_H_

/*
 * http://cslibrary.stanford.edu/103/LinkedListBasics.pdf
 *
 * This implementation defines the `head` as the first node of the list and the `tail` as the last.
 * There are no dummy nodes at the start nor end of the lists.
 */

#define DS_SB_IMPLEMENTATION
#include "string_buffer.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Struct representing nodes for singly linked lists.
typedef struct DS_LL_NodeSingly DS_LL_NodeSingly;
// Struct representing nodes for doubly linked lists.
typedef struct DS_LL_NodeDoubly DS_LL_NodeDoubly;
// Create and return a singly node for the given data with `next` pointing to NULL (head) if the data provided is not NULL.
static DS_LL_NodeSingly *ds_ll_create_singly(char *data);
// Create and return a doubly node for the given data with both `prev` and `next` pointing to NULL (head) if the data provided is not NULL.
static DS_LL_NodeDoubly *ds_ll_create_doubly(char *data);

static char *ds_ll_to_string(void *head);
static void ds_ll_print(void *head);
static size_t ds_ll_sizeof(void *head);
static DS_LL_NodeSingly *ds_ll_insert_front_singly(DS_LL_NodeSingly **head, char *data);
static DS_LL_NodeSingly *ds_ll_get_tail_singly(DS_LL_NodeSingly *head);
static DS_LL_NodeSingly *ds_ll_insert_singly(DS_LL_NodeSingly **head, char *data);
static size_t ds_ll_free_singly(DS_LL_NodeSingly *head);
static DS_LL_NodeSingly *ds_ll_find_singly(DS_LL_NodeSingly *head, char *data);

#ifdef __cplusplus
}
#endif

#ifdef DS_LL_IMPLEMENTATION
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DS_LL_NodeSingly {
    char *data;
    DS_LL_NodeSingly *next;
};

struct DS_LL_NodeDoubly {
    char *data;
    DS_LL_NodeDoubly *next;
    DS_LL_NodeDoubly *prev;
};

static char *ds_ll_to_string(void *head) {
    DS_LL_NodeSingly *p;
    DS_SB_StringBuffer *sb = ds_sb_create();

    for (p = (DS_LL_NodeSingly *)head; p != NULL; p = p->next) {
        ds_sb_append(sb, p->data);
        ds_sb_append(sb, (char *)" -> ");
    }
    ds_sb_append(sb, (char *)"NULL");

    char *str = (char *)malloc(sizeof(sb->data));
    strcpy(str, sb->data);
    ds_sb_free(sb);
    return str;
}

static void ds_ll_print(void *head) {
    char *str = ds_ll_to_string(head);
    printf("%s\n", str);
    free(str);
}

static size_t ds_ll_sizeof(void *head) {
    DS_LL_NodeSingly *p;
    size_t i = 0;
    for (p = (DS_LL_NodeSingly *)head; p != NULL; p = p->next) {
        i++;
    }
    return i;
}

static DS_LL_NodeSingly *ds_ll_create_singly(char *data) {
    if (data == NULL)
        return NULL;
    DS_LL_NodeSingly *head = (DS_LL_NodeSingly *)malloc(sizeof(DS_LL_NodeSingly));
    head->data = data;
    head->next = NULL;
    return head;
}

static DS_LL_NodeDoubly *ds_ll_create_doubly(char *data) {
    if (data == NULL)
        return NULL;
    DS_LL_NodeDoubly *head = (DS_LL_NodeDoubly *)malloc(sizeof(DS_LL_NodeDoubly));
    head->data = data;
    head->next = NULL;
    head->prev = NULL;
    return head;
}

static DS_LL_NodeSingly *ds_ll_insert_front_singly(DS_LL_NodeSingly **head, char *data) {
    if (data == NULL || head == NULL)
        return NULL;
    DS_LL_NodeSingly *new_head = ds_ll_create_singly(data);
    new_head->next = *head;
    return new_head;
}

static DS_LL_NodeSingly *ds_ll_get_tail_singly(DS_LL_NodeSingly *head) {
    if (head == NULL)
        return NULL;

    DS_LL_NodeSingly *p = head;
    while (p->next != NULL) {
        p = p->next;
    }
    return p;
}

static DS_LL_NodeSingly *ds_ll_insert_singly(DS_LL_NodeSingly **head, char *data) {
    DS_LL_NodeSingly *p = ds_ll_get_tail_singly(*head);
    if (p == NULL)
        return NULL;

    DS_LL_NodeSingly *node = ds_ll_create_singly(data);
    p->next = node;
    return node;
}

static size_t ds_ll_free_singly(DS_LL_NodeSingly *head) {
    size_t i = 0;
    DS_LL_NodeSingly *p = head;
    while (p != NULL) {
        DS_LL_NodeSingly *tmp = p->next;
        free(p);
        p = tmp;
        i++;
    }
    return i;
}

static DS_LL_NodeSingly *ds_ll_find_singly(DS_LL_NodeSingly *head, char *data) {
    if (head == NULL)
        return NULL;

    DS_LL_NodeSingly *p = head;
    if (strcmp(p->data, data) == 0)
        return p;

    if (p->next == NULL)
        return NULL;

    return ds_ll_find_singly(p->next, data);
}

#endif // DS_LL_IMPLEMENTATION
#endif // DS_LL_H_
