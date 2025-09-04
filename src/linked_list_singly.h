#ifndef DS_LL_SINGLY_H_
#define DS_LL_SINGLY_H_

/*
 * http://cslibrary.stanford.edu/103/LinkedListBasics.pdf
 *
 * This implementation defines the `head` as the first node of the list and the `tail` as the last.
 * There are no dummy nodes at the start nor end of the lists.
 */

#include <stdint.h>
#define DS_SB_IMPLEMENTATION
#include "string_buffer.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// A node of `DS_LL_SinglyList`.
typedef struct DS_LL_SinglyNode DS_LL_SinglyNode;
// A singly linked list holds its size and a pointer to its first node (head).
// Each node in the list consists of its data (in this case, a string) and a pointer to the next node.
typedef struct DS_LL_SinglyList DS_LL_SinglyList;
// Used as the return type of `ds_ll_singly_find_all()`. Holds the number of elements found and an array of pointers to them.
typedef struct DS_LL_SinglyArray DS_LL_SinglyArray;
// Creates an empty singly linked list.
static inline DS_LL_SinglyList *ds_ll_singly_create(void);
// Takes a singly linked list and frees it, returning the number of nodes freed.
static inline size_t ds_ll_singly_free(DS_LL_SinglyList *list);
// Returns the size of a singly linked list. Same as `list->size`.
static inline size_t ds_ll_singly_get_size(DS_LL_SinglyList *list);
// Returns the head of a singly linked list or NULL if empty. Same as `list->head`.
static inline DS_LL_SinglyNode *ds_ll_singly_get_head(DS_LL_SinglyList *list);
// Returns the tail of a singly linked list or NULL if empty.
static inline DS_LL_SinglyNode *ds_ll_singly_get_tail(DS_LL_SinglyList *list);
// Takes a singly linked list and a string and inserts a new node containing the string at the front of the list, returning a the size of the list after the operation.
static inline size_t ds_ll_singly_insert_front(DS_LL_SinglyList *list, char *data);
// Takes a singly linked list and a string and inserts a new node containing the string at the end of the list, returning a the size of the list after the operation.
static inline size_t ds_ll_singly_append(DS_LL_SinglyList *list, char *data);
// returns the position of a node in the list, or -1.
static inline size_t ds_ll_singly_find_node(DS_LL_SinglyList *list, DS_LL_SinglyNode *node);
// Finds and returns the first node that contains the data, or NULL.
static inline DS_LL_SinglyNode *ds_ll_singly_find_first(DS_LL_SinglyList *list, char *data);
// Finds all the nodes in the list that contains the data and returns a `DS_LL_SinglyArray` containing them, or NULL.
// You must call `ds_ll_singly_free_array()` on the result after you're done with it.
static inline DS_LL_SinglyArray *ds_ll_singly_find_all(DS_LL_SinglyList *list, char *data);
// Frees the result of `ds_ll_singly_find_all()`.
static inline void ds_ll_singly_free_array(DS_LL_SinglyArray *result);
// Takes a singly linked list and a pointer to one of its nodes and removes the node from the list, returning the size of the list after the operation.
static inline size_t ds_ll_singly_remove_node(DS_LL_SinglyList *list, DS_LL_SinglyNode *node);
// Takes a singly linked list and a string and removes the first node that contains the string from the list, returning the size of the list after the operation.
static inline size_t ds_ll_singly_remove_first(DS_LL_SinglyList *list, char *data);
// Takes a singly linked list and a string and removes all nodes that contains the string from the list, returning the size of the list after the operation.
static inline size_t ds_ll_singly_remove_all(DS_LL_SinglyList *list, char *data);
// Takes a singly linked list and a separator string and returns a single string containing all the data in the list.
static inline char *ds_ll_singly_join(DS_LL_SinglyList *list, char *separator);
// Prints the contents of the list.
static inline void ds_ll_singly_print(DS_LL_SinglyList *list);

#ifdef __cplusplus
}
#endif

#ifdef DS_LL_SINGLY_IMPLEMENTATION
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DS_LL_SinglyNode {
    char *data;
    DS_LL_SinglyNode *next;
};

struct DS_LL_SinglyList {
    DS_LL_SinglyNode *head;
    size_t size;
};

struct DS_LL_SinglyArray {
    DS_LL_SinglyNode **nodes;
    size_t size;
};

static inline DS_LL_SinglyList *ds_ll_singly_create() {
    DS_LL_SinglyList *list = (DS_LL_SinglyList *)malloc(sizeof(DS_LL_SinglyList));
    if (list == NULL)
        return NULL;
    list->head = NULL;
    list->size = 0;
    return list;
}

static inline size_t ds_ll_singly_free(DS_LL_SinglyList *list) {
    if (list == NULL)
        return 0;

    size_t i = 0;
    DS_LL_SinglyNode *p = list->head;
    while (p != NULL) {
        DS_LL_SinglyNode *tmp = p->next;
        free(p->data);
        free(p);
        p = tmp;
        i++;
    }
    free(list);
    return i;
}

static inline size_t ds_ll_singly_get_size(DS_LL_SinglyList *list) {
    if (list == NULL)
        return 0;
    return list->size;
}

static inline DS_LL_SinglyNode *ds_ll_singly_get_head(DS_LL_SinglyList *list) {
    if (list == NULL)
        return NULL;
    return list->head;
}

static inline DS_LL_SinglyNode *ds_ll_singly_get_tail(DS_LL_SinglyList *list) {
    if (list == NULL || list->head == NULL)
        return NULL;

    DS_LL_SinglyNode *p = list->head;
    while (p->next != NULL) {
        p = p->next;
    }
    return p;
}

static DS_LL_SinglyNode *create_singly_node(char *data) {
    if (data == NULL)
        return NULL;

    DS_LL_SinglyNode *node = (DS_LL_SinglyNode *)malloc(sizeof(DS_LL_SinglyNode));
    if (node == NULL)
        return NULL;

    node->data = strdup(data);
    node->next = NULL;
    return node;
}

static inline size_t ds_ll_singly_insert_front(DS_LL_SinglyList *list, char *data) {
    if (list == NULL)
        return 0;

    DS_LL_SinglyNode *new_head = create_singly_node(data);

    if (new_head == NULL)
        return list->size;

    new_head->next = list->head;
    list->head = new_head;
    list->size++;
    return list->size;
}

static inline size_t ds_ll_singly_append(DS_LL_SinglyList *list, char *data) {
    if (list == NULL)
        return 0;

    DS_LL_SinglyNode *node = create_singly_node(data);

    if (node == NULL)
        return list->size;

    DS_LL_SinglyNode *p = ds_ll_singly_get_tail(list);

    if (p == NULL) {
        // empty list
        list->head = node;
    } else {
        p->next = node;
    }
    list->size++;
    return list->size;
}

static inline size_t ds_ll_singly_find_node(DS_LL_SinglyList *list, DS_LL_SinglyNode *node) {
    if (list == NULL)
        return 0;

    DS_LL_SinglyNode *p;
    size_t pos = 0;

    for (p = list->head; p != node; p = p->next) {
        if (p->next == NULL)
            pos = -1;
        else
            pos++;
    }
    return pos;
}

static inline DS_LL_SinglyNode *ds_ll_singly_find_first(DS_LL_SinglyList *list, char *data) {
    if (list == NULL || data == NULL)
        return NULL;

    DS_LL_SinglyNode *p = list->head;
    while (p != NULL) {
        if (strcmp(p->data, data) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

static inline DS_LL_SinglyArray *ds_ll_singly_find_all(DS_LL_SinglyList *list, char *data) {
    if (list == NULL || data == NULL)
        return NULL;

    DS_LL_SinglyNode *p = list->head;
    DS_LL_SinglyArray *arr = (DS_LL_SinglyArray *)malloc(sizeof(DS_LL_SinglyArray));
    if (arr == NULL)
        return NULL;

    size_t capacity = 3;

    arr->nodes = (DS_LL_SinglyNode **)malloc(capacity * sizeof(DS_LL_SinglyNode *));
    if (arr->nodes == NULL) {
        free(arr);
        return NULL;
    }
    arr->size = 0;

    while (p != NULL) {
        if (strcmp(p->data, data) == 0) {
            if (arr->size + 1 > capacity) {
                capacity += 3;
                arr->nodes = (DS_LL_SinglyNode **)realloc(arr->nodes, capacity * sizeof(DS_LL_SinglyNode *));
                if (arr->nodes == NULL) {
                    free(arr);
                    return NULL;
                }
            }
            arr->nodes[arr->size] = p;
            arr->size++;
        }
        p = p->next;
    }
    return arr;
}

static inline void ds_ll_singly_free_array(DS_LL_SinglyArray *array) {
    if (array == NULL)
        return;
    free(array->nodes);
    free(array);
}

static inline size_t ds_ll_singly_remove_node(DS_LL_SinglyList *list, DS_LL_SinglyNode *node) {
    if (list == NULL)
        return 0;

    DS_LL_SinglyNode *cur = list->head;
    DS_LL_SinglyNode *prev = NULL;

    while (cur != NULL) {
        if (cur == node) {
            DS_LL_SinglyNode *next = cur->next;

            if (prev != NULL) {
                prev->next = next;
            } else {
                list->head = next;
            }
            free(cur->data);
            free(cur);

            list->size--;
            return list->size;
        }
        prev = cur;
        cur = cur->next;
    }
    return list->size;
}

static inline size_t ds_ll_singly_remove_first(DS_LL_SinglyList *list, char *data) {
    if (list == NULL)
        return 0;

    if (data == NULL)
        return list->size;

    // This is just for learning, so I'll reuse the existing functions...
    DS_LL_SinglyNode *p = ds_ll_singly_find_first(list, data);
    if (p == NULL)
        return list->size;

    return ds_ll_singly_remove_node(list, p);
}

static inline size_t ds_ll_singly_remove_all(DS_LL_SinglyList *list, char *data) {
    if (list == NULL)
        return 0;

    if (data == NULL)
        return list->size;

    DS_LL_SinglyNode *cur = list->head;
    DS_LL_SinglyNode *prev = NULL;

    while (cur != NULL) {
        if (strcmp(cur->data, data) == 0) {
            DS_LL_SinglyNode *next = cur->next;

            if (prev != NULL) {
                prev->next = next;
            } else {
                list->head = next;
            }
            free(cur->data);
            free(cur);

            list->size--;

            cur = next;
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
    return list->size;
}

static inline char *ds_ll_singly_join(DS_LL_SinglyList *list, char *separator) {
    if (list == NULL || separator == NULL)
        return NULL;

    DS_LL_SinglyNode *p;
    DS_SB_StringBuffer *sb = ds_sb_create();
    if (sb == NULL)
        return NULL;

    for (p = list->head; p != NULL; p = p->next) {
        ds_sb_append(sb, p->data);
        if (p->next != NULL)
            ds_sb_append(sb, separator);
    }
    if (sb->data == NULL || sb->size == 0) {
        ds_sb_free(sb);
        return NULL;
    }

    char *str = (char *)malloc(strlen(sb->data) + 1);
    if (str == NULL) {
        ds_sb_free(sb);
        return NULL;
    }
    if (sb->data == NULL)
        strcpy(str, "");
    else
        strcpy(str, sb->data);

    ds_sb_free(sb);
    return str;
}

static inline void ds_ll_singly_print(DS_LL_SinglyList *list) {
    char *str = ds_ll_singly_join(list, (char *)" -> ");
    if (str == NULL)
        return;
    if (strcmp(str, "") == 0)
        printf("NULL\n");
    else
        printf("%s -> NULL\n", str);
    free(str);
}
#endif // DS_LL_SINGLY_IMPLEMENTATION
#endif // DS_LL_SINGLY_H_
