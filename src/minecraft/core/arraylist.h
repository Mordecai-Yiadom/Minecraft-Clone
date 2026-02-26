#ifndef MINECRAFT_CORE_ARRAYLIST_H
#define MINECRAFT_CORE_ARRAYLIST_H

#include <stdlib.h>
#include "array.h"
#include "memtypes.h"
#include <stdbool.h>

#include "datastructures.h"

typedef struct ArrayList
{   
    Array array;
    int currentLength;
    MemoryType memoryType;
}ArrayList;

ArrayList ArrayList_create(int initialCapacity, int elementSize, MemoryType memoryType);

void ArrayList_destroy(ArrayList *arrayList);

int ArrayList_length(ArrayList *arrayList);

int ArrayList_size(ArrayList *arrayList);

int ArrayList_capacity(ArrayList *arrayList);

int ArrayList_elementSize(ArrayList *arrayList);

void ArrayList_get(ArrayList *arrayList, int index, byte *element);

void* ArrayList_getAddress(ArrayList* list, int index);

void ArrayList_add(ArrayList *arrayList, byte *element);

void ArrayList_remove(ArrayList *arrayList, int index);

void ArrayList_set(ArrayList *arrayList, int index, byte *element);

bool ArrayList_isEmpty(ArrayList *arrayList);

bool ArrayList_isFull(ArrayList *arrayList);

bool ArrayList_isValid(ArrayList *arrayList);

#endif