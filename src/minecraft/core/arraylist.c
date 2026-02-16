#include "arraylist.h"


ArrayList ArrayList_create(int initialCapacity, int elementSize)
{
    ArrayList arrayList;
    return arrayList;
}

ArrayList ArrayList_create(int initialCapacity, int elementSize, ArrayListResizePolicy resizePolicy)
{
    ArrayList list = {.resizePolicy=resizePolicy, .currentLength=0};
    list.array = Array_create(initialCapacity, elementSize);
    return list;
}

void ArrayList_destroy(ArrayList *arrayList)
{
    if(!arrayList) return;
    ArrayList_destroy(&arrayList->array);
}

int ArrayList_length(ArrayList *arrayList)
{
    if(!arrayList) return -1;
    return arrayList->currentLength;
}

int ArrayList_size(ArrayList *arrayList)
{
    if(!arrayList) return -1;
    return Array_size(&arrayList->array);
}

int ArrayList_elementSize(ArrayList *arrayList)
{
    if(!arrayList) return -1;
    return Array_elementSize(&arrayList->array);
}

void ArrayList_get(ArrayList *arrayList, int index, byte *element)
{
    if(!arrayList) return;
    Array_get(&arrayList->array, index, element);
}

void ArrayList_add(ArrayList *arrayList, byte *element)
{
    if(!arrayList) return;
    if(arrayList->currentLength == arrayList->array.length)
    {
        switch(arrayList->resizePolicy)
        {   
            case RESIZE_FALSE:
                return;

            case RESIZE_DOUBLE:
                Array_resize(&arrayList->array, arrayList->currentLength * 2);
                break;

            case RESIZE_INCREMENT:
                Array_resize(&arrayList->array, arrayList->currentLength + 1);
                break;
        }
    }
    
    Array_insert(&arrayList->array, arrayList->currentLength, element);
    arrayList->currentLength++;
}

void ArrayList_remove(ArrayList *arrayList, int index)
{
    if(!arrayList) return;
    if(!Array_isValidIndex(&arrayList->array, index)) return;

    arrayList->currentLength--;
    byte temp[256];
    for(int i = index; i < arrayList->currentLength; i++)
    {
        Array_get(&arrayList->array, i+1, temp);
        Array_insert(&arrayList->array, i, temp);
    }
}

void ArrayList_set(ArrayList *arrayList, int index, byte *element)
{
    if(!arrayList) return;
    Array_insert(&arrayList->array, index, element);
}

bool ArrayList_isEmpty(ArrayList *arrayList)
{
    if(!arrayList) return false;
    return (arrayList->currentLength == 0);
}