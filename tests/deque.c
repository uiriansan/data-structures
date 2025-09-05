#define DS_DQ_IMPLEMENTATION
#include "../src/deque.h"
#include <assert.h>

int main(int argc, char **argv) {
    DS_Deque *deque = ds_dq_create();
    ds_dq_print(deque);

    ds_dq_push_front(deque, "a");
    ds_dq_push_back(deque, "b");
    assert(ds_dq_get_size(deque) == 2);
    ds_dq_print(deque);

    char *a = ds_dq_pop_front(deque);
    assert(strcmp(a, "a") == 0);
    ds_dq_print(deque);
    free(a);

    a = ds_dq_pop_back(deque);
    assert(strcmp(a, "b") == 0);
    assert(ds_dq_get_size(deque) == 0);
    ds_dq_print(deque);
    free(a);

    ds_dq_push_back(deque, "a");
    ds_dq_push_back(deque, "b");
    ds_dq_push_back(deque, "c");
    ds_dq_push_back(deque, "d");
    ds_dq_push_back(deque, "e");

    assert(ds_dq_get_size(deque) == 5);

    ds_dq_push_front(deque, "f");
    ds_dq_push_front(deque, "g");
    ds_dq_push_front(deque, "h");
    ds_dq_push_front(deque, "i");
    ds_dq_push_front(deque, "j");

    assert(ds_dq_get_size(deque) == 10);
    ds_dq_print(deque);

    a = ds_dq_pop_back(deque);
    assert(strcmp(a, "e") == 0);
    assert(ds_dq_get_size(deque) == 9);
    ds_dq_print(deque);
    free(a);

    a = ds_dq_pop_front(deque);
    assert(strcmp(a, "j") == 0);
    assert(ds_dq_get_size(deque) == 8);
    ds_dq_print(deque);
    free(a);

    ds_dq_push_front(deque, "x");
    assert(ds_dq_get_size(deque) == 9);
    ds_dq_print(deque);

    assert(ds_dq_free(deque) == 9);

    return 0;
}
