#define DS_S_IMPLEMENTATION
#include "../src/stack.h"
#include <assert.h>

int main(int argc, char **argv) {
    DS_Stack *stack = ds_s_create();
    assert(ds_s_get_size(stack) == 0);
    ds_s_print(stack);

    ds_s_push(stack, "Hey");
    ds_s_push(stack, ", ");
    ds_s_push(stack, "there");
    assert(ds_s_get_size(stack) == 3);
    ds_s_print(stack);

    char *a = ds_s_pop(stack);
    assert(strcmp(a, "there") == 0);
    free(a);

    a = ds_s_pop(stack);
    assert(strcmp(a, ", ") == 0);
    free(a);

    a = ds_s_pop(stack);
    assert(strcmp(a, "Hey") == 0);
    assert(ds_s_get_size(stack) == 0);
    free(a);

    ds_s_print(stack);

    ds_s_push(stack, "a");
    assert(ds_s_get_size(stack) == 1);
    ds_s_push(stack, "b");
    assert(ds_s_get_size(stack) == 2);
    ds_s_push(stack, "c");
    assert(ds_s_get_size(stack) == 3);

    ds_s_print(stack);

    assert(ds_s_free(stack) == 3);

    return 0;
}
