#define DS_DA_IMPLEMENTATION
#include "../src/dynamic_array.h"
#include <assert.h>

int main(int argc, char **argv) {
    DS_DynamicArray *array = ds_da_create();
    assert(array->length == 0 && array->data != NULL);

    ds_da_print(array);

    ds_da_append(array, "This is a test");
    assert(array->length == 1);

    ds_da_print(array);

    ds_da_append(array, "a");
    ds_da_append(array, "b");
    ds_da_append(array, "c");
    assert(array->length == 4);

    ds_da_print(array);

    int len = ds_da_remove(array, 2);
    assert(len == 3);
    assert(array->data[array->length] == NULL);

    ds_da_print(array);

    assert(ds_da_append(array, "d") == 4);

    ds_da_append(array, "e");

    ds_da_print(array);

    assert(ds_da_remove(array, 0) == 4);

    ds_da_print(array);

    assert(ds_da_remove(array, 3) == 3);

    ds_da_print(array);

    return 0;
}
