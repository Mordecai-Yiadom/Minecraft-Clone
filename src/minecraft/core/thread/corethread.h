#ifndef CORE_THREAD_H
#define CORE_THREAD_H

#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include "coremutex.h"
typedef void* (*ThreadRoutine)(void* args);

typedef struct Thread
{
    pthread_t handle;
    ThreadRoutine routine;
}Thread;

Thread* Thread_create(ThreadRoutine routine, void* routineArgs);

void Thread_destroy(Thread* thread);

void* Thread_join(Thread* threadToJoin);

void Thread_sleep(unsigned int microseconds);

bool Thread_cancel(Thread* thread);

void* Thread_exit();

void Thread_detach(Thread* threadToDetach);

bool Thread_isValid(Thread* thread);

#endif