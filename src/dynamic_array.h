#ifndef DS_DA_H_
#define DS_DA_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DS_DA_INITIAL_CAPACITY 3

typedef struct DS_DynamicArray DS_DynamicArray;
static inline DS_DynamicArray *ds_da_create();
static inline int ds_da_append(DS_DynamicArray *arr, char *str);
static inline int ds_da_free(DS_DynamicArray *arr);
static inline void ds_da_print(DS_DynamicArray *arr);
static inline int ds_da_remove(DS_DynamicArray *arr, int index);

// I've implemented other relevant functions for arrays in linked_list.h.
// The logic is pretty much the same, so I will skip those here.

#ifdef __cplusplus
}
#endif

#ifdef DS_DA_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DS_DynamicArray {
    char **data;
    int length;
    int _capacity;
};

static inline DS_DynamicArray *ds_da_create() {
    DS_DynamicArray *arr = (DS_DynamicArray *)malloc(sizeof(DS_DynamicArray));
    arr->_capacity = DS_DA_INITIAL_CAPACITY;
    arr->data = (char **)malloc(arr->_capacity * sizeof(char *));
    arr->length = 0;
    return arr;
}

static inline int ds_da_append(DS_DynamicArray *arr, char *str) {
    if (str == NULL)
        return -1;

    if (arr->length == arr->_capacity) {
        arr->_capacity *= 2;
        arr->data = (char **)realloc(arr->data, arr->_capacity * sizeof(char *));
    }
    char *p = (char *)malloc(strlen(str));
    strcpy(p, str);
    arr->data[arr->length++] = p;

    return arr->length;
}

static inline int ds_da_free(DS_DynamicArray *arr) {
    if (arr == NULL || arr->data == NULL)
        return -1;

    size_t i;
    for (i = 0; i < arr->length; i++) {
        free(arr->data[i]);
    }
    free(arr->data);
    free(arr);
    return i;
}

static inline void ds_da_print(DS_DynamicArray *arr) {
    if (arr == NULL || arr->data == NULL) {
        printf("NULL\n");
        return;
    }
    printf("[");

    for (size_t i = 0; i < arr->length; i++) {
        printf("%s", arr->data[i]);

        if (i + 1 < arr->length)
            printf(", ");
    }
    printf("]\n");
}

static inline int ds_da_remove(DS_DynamicArray *arr, int index) {
    if (arr == NULL || index >= arr->length)
        return -1;

    free(arr->data[index]);
    arr->length--;

    for (size_t i = index; i < arr->length; i++) {
        arr->data[i] = arr->data[i + 1];

        if (i + 1 == arr->length)
            arr->data[i + 1] = NULL;
    }
    return arr->length;
}
#endif // DS_DA_IMPLEMENTATION
#endif // DS_DA_H_
