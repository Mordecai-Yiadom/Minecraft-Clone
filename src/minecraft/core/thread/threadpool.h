#ifndef CORE_THREADPOOL_H
#define CORE_THREADPOOL_H

#include "corethread.h"
#include "../util/queue.h"

#define THREADPOOL_MAX 5

typedef struct ThreadPool
{
    Thread threads[THREADPOOL_MAX];
    Queue jobQueue;
}ThreadPool;

typedef struct ThreadPoolTask
{
    void* task;
    void* args;
}ThreadPoolTask;

#define THREADPOOLTASK(t, a) ((ThreadPoolTask){.task=t, .args=a})

ThreadPool* ThreadPool_create(int threadCount);

void ThreadPool_enqueueTask(ThreadPoolTask task);


#endif