#define DS_LL_DOUBLY_IMPLEMENTATION
#include "../src/linked_list_doubly.h"
#include <assert.h>

int main(int argc, char **argv) {
    DS_LL_DoublyNode *head = ds_ll_doubly_create_node(NULL);
    ds_ll_doubly_print(head);

    assert(ds_ll_doubly_append(head, "a") == head);
    assert(ds_ll_doubly_get_size(head) == 1);
    ds_ll_doubly_print(head);

    assert(ds_ll_doubly_append(head, "b") != NULL);
    assert(ds_ll_doubly_get_size(head) == 2);
    ds_ll_doubly_print(head);

    ds_ll_doubly_remove(&head, head);
    assert(ds_ll_doubly_get_size(head) == 1);
    ds_ll_doubly_print(head);

    ds_ll_doubly_remove(&head, head);
    assert(ds_ll_doubly_get_size(head) == 0);
    ds_ll_doubly_print(head);

    assert(ds_ll_doubly_insert_front(&head, "a") == head);
    assert(ds_ll_doubly_get_size(head) == 1);
    assert(ds_ll_doubly_get_tail(head) == head);
    ds_ll_doubly_print(head);

    assert(ds_ll_doubly_insert_front(&head, "b") != NULL);
    assert(ds_ll_doubly_get_size(head) == 2);
    ds_ll_doubly_print(head);

    assert(ds_ll_doubly_append(head, "c") != NULL);
    assert(ds_ll_doubly_get_size(head) == 3);
    ds_ll_doubly_print(head);

    assert(ds_ll_doubly_append(head, "d") != NULL);
    assert(ds_ll_doubly_get_size(head) == 4);
    ds_ll_doubly_print(head);

    ds_ll_doubly_remove(&head, head->next->next);
    assert(ds_ll_doubly_get_size(head) == 3);
    ds_ll_doubly_print(head);

    ds_ll_doubly_remove(&head, ds_ll_doubly_get_tail(head));
    assert(ds_ll_doubly_get_size(head) == 2);
    ds_ll_doubly_print(head);
}
