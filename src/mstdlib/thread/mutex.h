#ifndef MSTDLIB_MUTEX_H
#define MSTDLIB_MUTEX_H

#include <pthread.h>

typedef struct Mutex
{
    pthread_mutex_t handle;
}Mutex;

Mutex* Mutex_create();

void Mutex_destroy(Mutex* mutex);

void Mutex_lock(Mutex* mutex);

void Mutex_unlock(Mutex* mutex);



#endif