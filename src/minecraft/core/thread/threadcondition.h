#ifndef CORE_THREADCONDITION_H
#define CORE_THREADCONDITION_H

#include "coremutex.h"

typedef struct ThreadCondition
{
    pthread_cond_t handle;
}ThreadCondition;

ThreadCondition* ThreadCondition_create();

void ThreadCondition_destroy(ThreadCondition* threadCondition);

void ThreadCondition_wait(ThreadCondition* threadCondtition, Mutex* mutex);

void ThreadCondition_signal(ThreadCondition* threadCondition);

void ThreadCondition_broadcast(ThreadCondition* threadCondition);



#endif