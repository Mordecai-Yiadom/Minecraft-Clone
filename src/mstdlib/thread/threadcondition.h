#ifndef MSTDLIB_THREADCONDITION_H
#define MSTDLIB_THREADCONDITION_H

#include "mutex.h"

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