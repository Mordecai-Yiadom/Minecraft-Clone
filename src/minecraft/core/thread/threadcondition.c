#include "threadcondition.h"
#include <stdlib.h>

ThreadCondition* ThreadCondition_create()
{
    ThreadCondition *threadCondition = calloc(1, sizeof(ThreadCondition));
    pthread_cond_init(&threadCondition->handle, NULL);
    return threadCondition;
}

void ThreadCondition_destroy(ThreadCondition* threadCondition)
{
    if(!threadCondition) return;
    pthread_cond_destroy(&threadCondition->handle);
    free(threadCondition);
}

void ThreadCondition_wait(ThreadCondition* threadCondition, Mutex* mutex)
{
    if(!threadCondition || !mutex) return;
    pthread_cond_wait(&threadCondition->handle, &mutex->handle);
}

void ThreadCondition_signal(ThreadCondition* threadCondition)
{
    if(!threadCondition) return;
    pthread_cond_signal(&threadCondition->handle);
}

void ThreadCondition_broadcast(ThreadCondition* threadCondition)
{
    if(!threadCondition) return;
    pthread_cond_broadcast(&threadCondition->handle);
}
