#define CORE_THREADPOOL_C
#include "threadpool.h"

ThreadPool* ThreadPool_create(int threadCount)
{
    if(threadCount < THREADPOOL_MIN_SIZE) threadCount = THREADPOOL_MIN_SIZE;
    else if(threadCount > THREADPOOL_MAX_SIZE) threadCount = THREADPOOL_MAX_SIZE;

    ThreadPool *threadPool = calloc(1, sizeof(ThreadPool));
    threadPool->threadCount = threadCount;
    threadPool->taskQueue = Queue_create(THREADPOOL_TASKQUEUE_MAX_SIZE, sizeof(ThreadPoolTask), STATIC_MEMORY);

    threadPool->taskQueueMutex = Mutex_create();

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
}

void ThreadPool_sumbitTask(ThreadPool* threadPool, ThreadPoolTask task)
{
    if(!threadPool || !ThreadPoolTask_isValid(task)) return;
    
    Mutex_lock(threadPool->taskQueueMutex);
    Queue_enqueue(&threadPool->taskQueue, (byte*)&task);
    Mutex_unlock(threadPool->taskQueueMutex);
}

bool ThreadPoolTask_isValid(ThreadPoolTask task)
{
    return (task.routine != NULL);
}

static inline void* ThreadPool_pollTasks(void* threadPool)
{
    if(!threadPool) return NULL;
    
    while(true)
    {
        if(Queue_length(&((ThreadPool*)threadPool)->taskQueue) > 0)
        {
            ThreadPoolThread_executeTask(ThreadPoolThread_getNextTask(threadPool));
        }
        else Thread_sleep(10000);
    }
    return NULL;
}

static ThreadPoolTask ThreadPoolThread_getNextTask(ThreadPool* threadPool)
{
    if(!threadPool) return THREADPOOLTASK(NULL, NULL);

    ThreadPoolTask task;
    Mutex_lock(threadPool->taskQueueMutex);

    Queue_peek(&threadPool->taskQueue, (byte*)&task);
    Queue_dequeue(&threadPool->taskQueue);

    Mutex_unlock(threadPool->taskQueueMutex);

    return task;
}

static inline void ThreadPoolThread_executeTask(ThreadPoolTask task)
{
    if(!task.routine) return;
    task.routine(task.args);
}