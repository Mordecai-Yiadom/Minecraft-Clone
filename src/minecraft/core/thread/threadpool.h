#ifndef CORE_THREADPOOL_H
#define CORE_THREADPOOL_H

#include "corethread.h"
#include "threadcondition.h"
#include "../util/queue.h"

#define THREADPOOL_MIN_SIZE 1
#define THREADPOOL_MAX_SIZE 5
#define THREADPOOL_TASKQUEUE_MAX_SIZE 1000

typedef struct ThreadPool
{
    Thread* threads[THREADPOOL_MAX_SIZE];
    Queue taskQueue;
    Mutex* taskQueueMutex;
    ThreadCondition *taskQueueNotEmptyCondition;
    int threadCount;
}ThreadPool;

typedef struct ThreadPoolTask
{
    ThreadRoutine routine;
    void* args;
}ThreadPoolTask;

#define THREADPOOLTASK(r, a) ((ThreadPoolTask){.routine=r, .args=a})

ThreadPool* ThreadPool_create(int threadCount);

void ThreadPool_destroy(ThreadPool* threadPool);

void ThreadPool_sumbitTask(ThreadPool* threadPool, ThreadPoolTask task);

void ThreadPool_detatch(ThreadPool* threadPool);

void ThreadPool_join(ThreadPool* threadPool);

bool ThreadPoolTask_isValid(ThreadPoolTask task);



#ifdef CORE_THREADPOOL_C
    static void* ThreadPool_pollTasks(void* threadPool);
    static inline ThreadPoolTask ThreadPoolThread_getNextTask(ThreadPool* threadPool);
    static inline void ThreadPoolThread_executeTask(ThreadPoolTask task);
#endif

#endif