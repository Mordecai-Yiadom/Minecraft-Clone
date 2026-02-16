#include "array.h"
#include <stdlib.h>


Array Array_create(int length, int elementSize)
{
    if(length < 0) length = 0;
    Array array = {.length=length, .elementSize=elementSize};
    array.data = calloc(length, elementSize);
    return array;
}

void Array_destroy(Array *array)
{   
    if(!array) return;
    free(array->data);
}

int Array_length(Array *array)
{
    if(!array) return -1;
    return array->length;
}

int Array_elementSize(Array *array)
{
    if(!array) return -1;
    return array->elementSize;
}

void Array_get(Array *array, int index, byte *element)
{
    if(!array || !element) return;
    if(!Array_isValidIndex(array, index)) return;
    
    for(int i = 0; i < array->elementSize; i++)
    {
        element[i] = array->data[(index * array->elementSize) + i];
    }
}

void Array_insert(Array *array, int index, byte *element)
{
    if(!array || !element) return;
    if(!Array_isValidIndex(array, index)) return;

    for(int i = 0; i < array->elementSize; i++)
    {   
        array->data[(index * array->elementSize) + i] = element[i];
    }
}

int Array_size(Array *array)
{
    if(!array) return -1;
    return array->elementSize * array->length;
}

void Array_resize(Array *array, int newLength)
{
    if(!array || newLength < 0) return;
    array->length = newLength;
    realloc(array->data, newLength * array->elementSize);
}



void Array_swap(Array *array, int index1, int index2)
{
    if(!array) return;
    if(!Array_isValidIndex(array, index1) 
    || !Array_isValidIndex(array, index2)) return;
    if(index1 == index2) return;

    byte temp1[256];
    byte temp2[256];
    Array_get(array, index1, temp1);
    Array_get(array, index2, temp2);

    //Swap
    Array_insert(array, index1, temp2);
    Array_insert(array, index2, temp1);
}

bool Array_isValidIndex(Array *array, int index)
{
    if(!array) return false;
    return ((index > -1) && (index < array->length));
}