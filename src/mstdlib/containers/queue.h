#ifndef MSTDLIB_QUEUE_H
#define MSTDLIB_QUEUE_H

#include "arraylist.h"
#include "../containers.h"

typedef struct Queue
{
    Array array;
    int length;
    int frontIndex;
    int backIndex;
    MemoryType memoryType;
}Queue;

#ifdef MSTDLIB_QUEUE_C
    static inline void StaticQueue_enqueue(Queue *queue, byte* element);
    static inline void StaticQueue_dequeue(Queue *queue);

    // static inline void DynamicQueue_enqueue(Queue *queue, byte* element);
    // static inline void DynamicQueue_dequeue(Queue *queue);
#endif

Queue Queue_create(int initialCapacity, int elementSize, MemoryType memoryType);

void Queue_destroy(Queue *queue);

void Queue_enqueue(Queue *queue, byte* element);

void Queue_dequeue(Queue *queue);

void Queue_peek(Queue *queue, byte *element);

int Queue_length(Queue *queue);

bool Queue_isFull(Queue *queue);

bool Queue_isEmpty(Queue *queue);

void Queue_clear(Queue *queue);




#endif