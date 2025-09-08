// Simplified implementation of a stack using the already existing dynamic arrays.

#ifndef DS_S_H_
#define DS_S_H_

#define DS_DA_IMPLEMENTATION
#include "dynamic_array.h"

#ifdef __cplusplus
extern "C" {
#endif

// Stack is a LIFO data structure (Last In, First Out).
typedef struct DS_DynamicArray DS_Stack;
// Create a stack;
static inline DS_Stack *ds_s_create();
// Free a stack and its data.
static inline size_t ds_s_free(DS_Stack *stack);
// Get the size of a stack.
static inline size_t ds_s_get_size(DS_Stack *stack);
// Add an element to the top of the stack.
static inline void ds_s_push(DS_Stack *stack, char *data);
// Get the element at the top of the stack.
// This returns a `char *` that must be freed with `free()` later.
static inline char *ds_s_top(DS_Stack *stack);
// Get the element at the top of the stack and removes it from the list.
// This returns a `char *` that must be freed with `free()` later.
static inline char *ds_s_pop(DS_Stack *stack);
// Print the stack.
static inline void ds_s_print(DS_Stack *stack);

#ifdef __cplusplus
}
#endif

#ifdef DS_S_IMPLEMENTATION
static inline DS_Stack *ds_s_create() {
    DS_Stack *s = ds_da_create();
    return s;
}

static inline size_t ds_s_free(DS_Stack *stack) {
    return ds_da_free(stack);
}

static size_t ds_s_get_size(DS_Stack *stack) {
    if (stack == NULL)
        return 0;
    return stack->length;
}

static void ds_s_push(DS_Stack *stack, char *data) {
    ds_da_append(stack, data);
}

static char *ds_s_top(DS_Stack *stack) {
    if (stack == NULL)
        return NULL;

    return strdup(stack->data[stack->length - 1]);
}

static char *ds_s_pop(DS_Stack *stack) {
    if (stack == NULL)
        return NULL;

    char *top = ds_s_top(stack);
    if (top == NULL)
        return NULL;

    ds_da_remove(stack, stack->length - 1);
    return top;
}

static inline void ds_s_print(DS_Stack *stack) {
    if (stack == NULL || stack->data == NULL || stack->length == 0) {
        printf("NULL\n");
        return;
    }
    for (int i = stack->length - 1; i >= 0; i--) {
        if (i == stack->length - 1)
            printf("-> %s\n", stack->data[i]);
        else
            printf("   %s\n", stack->data[i]);
    }
}

#endif // DS_S_IMPLEMENTATION
#endif // DS_S_H_
