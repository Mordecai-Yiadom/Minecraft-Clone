#define MINECRAFT_CORE_QUEUE_C
#include "queue.h"

Queue Queue_create(int initialCapacity, int elementSize, MemoryType memoryType)
{
    Queue queue = {.frontIndex=0, .backIndex=-1, .length=0, .memoryType=memoryType};
    queue.array = Array_create(initialCapacity, elementSize);
    return queue;
}

void Queue_destroy(Queue *queue)
{
    if(!queue) return;
    Array_destroy(&queue->array);
}


void Queue_enqueue(Queue *queue, byte* element)
{
    if(!queue || !element) return;

    switch(queue->memoryType)
    {
        case STATIC_MEMORY:
            StaticQueue_enqueue(queue, element);
            return;
        case DYNAMIC_MEMORY:
            break;
    }
}

void Queue_dequeue(Queue *queue)
{
    if(!queue) return;

    switch(queue->memoryType)
    {
        case STATIC_MEMORY:
            StaticQueue_dequeue(queue);
            return;
        case DYNAMIC_MEMORY:
            break;
    }
}

void Queue_peek(Queue *queue, byte *element)
{
    if(Queue_isEmpty(queue) || !element) return;
    Array_get(&queue->array, queue->frontIndex, element);
}

int Queue_length(Queue *queue)
{
    if(!queue) return -1;
    return queue->length;
}

bool Queue_isFull(Queue *queue)
{
    if(!queue) return true;
    return (queue->length == queue->array.length) && (queue->memoryType == STATIC_MEMORY);
}

bool Queue_isEmpty(Queue *queue)
{
    if(!queue) return true;
    return queue->length < 1;
}


void Queue_clear(Queue *queue)
{
    if(Queue_isEmpty(queue)) return;
    queue->frontIndex = 0;
    queue->backIndex = -1;
    queue->length = 0;
    
}


static inline void StaticQueue_enqueue(Queue *queue, byte* element)
{
    if(Queue_isFull(queue)) return;

    //backindex = backindex % capacity
    queue->backIndex = (queue->backIndex + 1) % queue->array.length;
    Array_insert(&queue->array, queue->backIndex, element);
    queue->length++;
}

static inline void StaticQueue_dequeue(Queue *queue)
{
    if(Queue_isEmpty(queue)) return;
    queue->frontIndex = (queue->frontIndex + 1) % queue->array.length;
    queue->length--;
}
