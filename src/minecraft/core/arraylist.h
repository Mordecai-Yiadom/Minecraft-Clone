#ifndef MINECRAFT_CORE_ARRAYLIST_H
#define MINECRAFT_CORE_ARRAYLIST_H

#include "array.h"
#include "memtypes.h"
#include <stdbool.h>

typedef enum ArrayListResizePolicy
{   
    RESIZE_FALSE,
    RESIZE_DOUBLE,
    RESIZE_INCREMENT,

}ArrayListResizePolicy;

typedef struct ArrayList
{   
    Array array;
    int currentLength;
    ArrayListResizePolicy resizePolicy;
}ArrayList;

ArrayList ArrayList_create(int initialCapacity, int elementSize, ArrayListResizePolicy resizePolicy);

void ArrayList_destroy(ArrayList *arrayList);

int ArrayList_length(ArrayList *arrayList);

int ArrayList_size(ArrayList *arrayList);

int ArrayList_capacity(ArrayList *arrayList);

int ArrayList_elementSize(ArrayList *arrayList);

void ArrayList_get(ArrayList *arrayList, int index, byte *element);

void ArrayList_add(ArrayList *arrayList, byte *element);

void ArrayList_remove(ArrayList *arrayList, int index);

void ArrayList_set(ArrayList *arrayList, int index, byte *element);

bool ArrayList_isEmpty(ArrayList *arrayList);

#endif