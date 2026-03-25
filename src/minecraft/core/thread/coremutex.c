#include "coremutex.h"

#include <stdlib.h>


Mutex* Mutex_create()
{
    Mutex *mutex = calloc(1, sizeof(Mutex));

    pthread_mutex_init(&mutex->handle, NULL);
    return mutex;
}

void Mutex_destroy(Mutex* mutex)
{
    if(!mutex) return;
    pthread_mutex_destroy(&mutex->handle);
    
}

void Mutex_lock(Mutex* mutex)
{   
    if(!mutex) return;
    pthread_mutex_lock(&mutex->handle);
}

void Mutex_unlock(Mutex* mutex)
{
    if(!mutex) return;
    pthread_mutex_unlock(&mutex->handle);
}


