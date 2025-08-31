#define DS_LL_IMPLEMENTATION
#include "../src/linked_list.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    DS_LL_SinglyList *list = ds_ll_singly_create();

    // NULL list asserts:
    assert(ds_ll_singly_get_head(list) == NULL && "`ds_ll_singly_get_head()` failed on empty list.");
    assert(ds_ll_singly_get_tail(list) == NULL && "`ds_ll_singly_get_tail()` failed on empty list.");
    assert(ds_ll_singly_get_size(list) == 0 && "`ds_ll_singly_get_size()` failed on empty list.");
    assert(ds_ll_singly_find_first(list, "some") == NULL && "`ds_ll_singly_find_first()` failed on empty list.");
    DS_LL_SinglyArray *null_arr = ds_ll_singly_find_all(list, "some");
    assert(null_arr->size == 0 && "`ds_ll_singly_find_all()` failed on empty list.");
    ds_ll_singly_free_array(null_arr);
    assert(ds_ll_singly_remove_first(&list, "some") == 0 && "`ds_ll_singly_remove_first()` failed on empty list.");
    assert(ds_ll_singly_remove_all(&list, "some") == 0 && "`ds_ll_singly_remove_all()` failed on empty list.");
    assert(ds_ll_singly_join(list, "") == NULL && "`ds_ll_singly_join()` failed on empty list.");
    ds_ll_singly_print(list);
    assert(ds_ll_singly_free(list) == 0 && "`ds_ll_singly_free()` failed on empty list.");

    // Common asserts:
    list = ds_ll_singly_create();

    const char *abc = "abcdefghijklmnopqrstuvwxyz";
    for (size_t i = 0; i < strlen(abc); i++) {
        char buf[2];
        buf[0] = abc[i];
        buf[1] = 0;
        size_t new_size = ds_ll_singly_append(&list, buf);
        assert(new_size == i + 1 && "ABC: `new_size` doesn't match the expected size of the list.");
    }
    ds_ll_singly_print(list);
    DS_LL_SinglyArray *arr = ds_ll_singly_find_all(list, "x");
    assert(arr && arr->size == 1 && "X: array size not equals to 1.");
    ds_ll_singly_free_array(arr);

    ds_ll_singly_insert_front(&list, "x");
    ds_ll_singly_insert_front(&list, "test");
    ds_ll_singly_print(list);
    arr = ds_ll_singly_find_all(list, "x");
    assert(arr && arr->size == 2 && "X: array size not equals to 2.");
    ds_ll_singly_free_array(arr);

    const char *expected_res = "test - x - a - b - c - d - e - f - g - h - i - j - k - l - m - n - o - p - q - r - s - t - u - v - w - x - y - z";
    char *j_str = ds_ll_singly_join(list, " - ");
    assert(strcmp(j_str, expected_res) == 0 && "ABC: `ds_ll_singly_join()` did not match the expected result.");
    free(j_str);

    ds_ll_singly_remove_first(&list, "test");

    DS_LL_SinglyNode *z_node = ds_ll_singly_find_first(list, "z");
    assert(z_node != NULL && strcmp(z_node->data, "z") == 0 && "`z_node` has the wrong data.");
    ds_ll_singly_remove_node(&list, z_node);
    ds_ll_singly_print(list);

    ds_ll_singly_remove_all(&list, "x");
    ds_ll_singly_print(list);

    assert(ds_ll_singly_free(list) == strlen(abc) - 2 && "ABC: incorrect # of freed elements.");
    return 0;
}
