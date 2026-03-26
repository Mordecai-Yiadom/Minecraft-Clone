#include "corethread.h"

#include <stdlib.h> 

Thread* Thread_create(ThreadRoutine routine, void* routineArgs)
{
    if(!routine) return NULL;

    Thread *thread = calloc(1, sizeof(Thread));
    pthread_create(&thread->handle, NULL, routine, routineArgs);
    return thread;
}

void Thread_destroy(Thread* thread)
{
    if(!thread) return;
    free(thread);
}

void* Thread_join(Thread* threadToJoin)
{
    if(!Thread_isValid(threadToJoin)) return NULL;

    void* result = NULL;
    pthread_join(threadToJoin->handle, &result);
    return result;
}

bool Thread_cancel(Thread* thread)
{
    if(!Thread_isValid(thread)) return false;
    return pthread_cancel(thread->handle);
}

void* Thread_exit()
{
    void* exitStatus = NULL;
    pthread_exit(exitStatus);
    return exitStatus;
}


void Thread_sleep(unsigned int microseconds)
{
    usleep(microseconds);
}


void Thread_detach(Thread* thread)
{
    if(!Thread_isValid(thread)) return;
    pthread_detach(thread->handle);
}

bool Thread_isValid(Thread* thread)
{
    if(!thread) return false;
    return (thread->handle != 0 && thread->routine != 0);
}
