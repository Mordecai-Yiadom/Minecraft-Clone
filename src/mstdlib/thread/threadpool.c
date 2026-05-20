#define CORE_THREADPOOL_C
#include "threadpool.h"
#include <stdio.h>
ThreadPool* ThreadPool_create(int threadCount)
{
    if(threadCount < THREADPOOL_MIN_SIZE) threadCount = THREADPOOL_MIN_SIZE;
    else if(threadCount > THREADPOOL_MAX_SIZE) threadCount = THREADPOOL_MAX_SIZE;

    ThreadPool *threadPool = calloc(1, sizeof(ThreadPool));
    threadPool->threadCount = threadCount;
    threadPool->taskQueue = Queue_create(THREADPOOL_TASKQUEUE_MAX_SIZE, sizeof(ThreadPoolTask), STATIC_MEMORY);

    threadPool->taskQueueMutex = Mutex_create();
    threadPool->taskQueueNotEmptyCondition = ThreadCondition_create();

    for(int i = 0; i < threadCount; i++)
    {
        threadPool->threads[i] = Thread_create(ThreadPool_pollTasks, threadPool);
    }

    return threadPool;
}



void ThreadPool_destroy(ThreadPool* threadPool)
{
    if(!threadPool) return;

    for(int i = 0; i < threadPool->threadCount; i++)
    {
        Thread_cancel(threadPool->threads[i]);
        Thread_destroy(threadPool->threads[i]);
    }

    Mutex_destroy(threadPool->taskQueueMutex);
    ThreadCondition_destroy(threadPool->taskQueueNotEmptyCondition);
}

void ThreadPool_sumbitTask(ThreadPool* threadPool, ThreadPoolTask task)
{
    if(!threadPool || !ThreadPoolTask_isValid(task)) return;
    
    Mutex_lock(threadPool->taskQueueMutex);
    Queue_enqueue(&threadPool->taskQueue, (byte*)&task);
    Mutex_unlock(threadPool->taskQueueMutex);

    if(Queue_length(&threadPool->taskQueue) > 1) 
        ThreadCondition_broadcast(threadPool->taskQueueNotEmptyCondition);
    else 
        ThreadCondition_signal(threadPool->taskQueueNotEmptyCondition);
}

void ThreadPool_detatch(ThreadPool* threadPool)
{
    if(!threadPool) return;
    for(int i = 0; i < threadPool->threadCount; i++)
    {
        Thread_detach(threadPool->threads[i]);
    }
}

void ThreadPool_join(ThreadPool* threadPool)
{
    if(!threadPool) return;

    for(int i = 0; i < threadPool->threadCount; i++)
    {
        Thread_join(threadPool->threads[i]);
    }
}

bool ThreadPoolTask_isValid(ThreadPoolTask task)
{
    return (task.routine != NULL);
}

static inline void* ThreadPool_pollTasks(void* args)
{
    if(!args) return NULL;

    ThreadPool *threadPool = args;
    ThreadPoolTask currentTask;
    while(true)
    {   
        currentTask = THREADPOOLTASK(NULL, NULL);
        Mutex_lock(threadPool->taskQueueMutex);

        while(Queue_length(&threadPool->taskQueue) < 1) 
            ThreadCondition_wait(threadPool->taskQueueNotEmptyCondition, threadPool->taskQueueMutex);
        
        
        currentTask = ThreadPoolThread_getNextTask(threadPool);
        Mutex_unlock(threadPool->taskQueueMutex);

        ThreadPoolThread_executeTask(currentTask);
    }
    return NULL;
}

static ThreadPoolTask ThreadPoolThread_getNextTask(ThreadPool* threadPool)
{
    if(!threadPool) return THREADPOOLTASK(NULL, NULL);

    ThreadPoolTask task;

    Queue_peek(&threadPool->taskQueue, (byte*)&task);
    Queue_dequeue(&threadPool->taskQueue);

    return task;
}

static inline void ThreadPoolThread_executeTask(ThreadPoolTask task)
{
    if(!task.routine) return;
    task.routine(task.args);
}