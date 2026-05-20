#ifndef MSTDLIB_ARRAY_H
#define MSTDLIB_ARRAY_H

#include <stdbool.h>
#include "../memtypes.h"

typedef enum ArrayError
{
    ARRAY_NO_ERROR,
    ARRAY_NULL,
    ARRAY_INVALID_ARG,
    ARRAY_INVALID_INDEX,
    ARRAY_
}ArrayError;

typedef struct Array
{
    byte *data;
    int length;
    int elementSize;
}Array;

Array Array_create(int length, int elementSize);

void Array_destroy(Array *array);

int Array_length(Array *array);

int Array_elementSize(Array *array);

void Array_get(Array *array, int index, byte *element);

void Array_insert(Array *array, int index, byte *element);

int Array_size(Array *array);

void Array_resize(Array *array, int newLength);

void Array_pack(Array *array, int *holes, int holeCount);

void Array_swap(Array *array, int index1, int index2);

bool Array_isValidIndex(Array *array, int index);

void* Array_getAddress(Array *array, int index);

bool Array_isValid(Array *array);

void Array_clear(Array *array);

#endif