#define DS_LL_DOUBLY_IMPLEMENTATION
#include "../src/linked_list_doubly.h"
#include <assert.h>

int main(int argc, char **argv) {
    DS_LL_DoublyList *list = ds_ll_doubly_create();
    ds_ll_doubly_print(list);

    assert(ds_ll_doubly_append(list, "a") == 1);
    assert(ds_ll_doubly_append(list, "b") == 2);

    ds_ll_doubly_print(list);

    assert(ds_ll_doubly_insert_front(list, "c") == 3);
    assert(ds_ll_doubly_insert_front(list, "d") == 4);

    ds_ll_doubly_print(list);

    assert(ds_ll_doubly_remove(list, list->head) == 3);

    ds_ll_doubly_print(list);

    assert(ds_ll_doubly_remove(list, list->tail) == 2);

    ds_ll_doubly_print(list);

    assert(ds_ll_doubly_remove(list, list->tail->prev) == 1);

    ds_ll_doubly_print(list);
}
