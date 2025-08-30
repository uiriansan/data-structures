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
    assert(arr->size == 1 && "X: array size not equals to 1.");
    ds_ll_singly_free_array(arr);

    ds_ll_singly_append(&list, "x");
    ds_ll_singly_print(list);
    arr = ds_ll_singly_find_all(list, "x");
    assert(arr != NULL && arr->size == 2 && "X: array size not equals to 2.");
    ds_ll_singly_free_array(arr);

    const char *expected_res = "a - b - c - d - e - f - g - h - i - j - k - l - m - n - o - p - q - r - s - t - u - v - w - x - y - z";
    // assert(strcmp(ds_ll_singly_join(list, " - "), expected_res) == 0 && "ABC: `ds_ll_singly_join()` did not match the expected result.");
    // assert(ds_ll_singly_free(list) == strlen(abc) && "ABC: incorrect # of freed elements.");

    return 0;
}
