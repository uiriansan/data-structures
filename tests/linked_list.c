#define DS_LL_IMPLEMENTATION
#include "../src/linked_list.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    DS_LL_NodeSingly *head = ds_ll_create_singly("hey");
    head = ds_ll_insert_front_singly(&head, "there");
    head = ds_ll_insert_front_singly(&head, "this");
    head = ds_ll_insert_front_singly(&head, "is");
    head = ds_ll_insert_front_singly(&head, "a");

    assert(ds_ll_sizeof(head) == 5 && "Assertion failed: list size is incorrect.");

    ds_ll_append_singly(&head, "message");
    ds_ll_append_singly(&head, "from");
    ds_ll_append_singly(&head, "linked");
    ds_ll_append_singly(&head, "list");

    assert(ds_ll_sizeof(head) == 9 && "Assertion failed: list size is incorrect.");

    char *str = ds_ll_to_string(head);
    assert(strcmp(str, "a -> is -> this -> there -> hey -> message -> from -> linked -> list -> NULL") == 0 && "Assertion failed: incorrect output of 'ds_ll_to_string'");
    free(str);

    DS_LL_NodeSingly *fd = ds_ll_find_singly(head, "from");
    assert(strcmp(fd->data, "from") == 0 && "Assertion failed: incorrect value for 'fd'.");

    DS_LL_NodeSingly *xd = ds_ll_find_singly(head, "");
    assert(xd == NULL && "Assertion failed: 'xd' is not NULL.");

    size_t freed = ds_ll_free_singly(head);
    assert(freed == 9 && "Assertion failed: freed != 9");

    return 0;
}
