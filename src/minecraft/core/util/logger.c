#include "logger.h"

void Logger_logError(ErrorType type, char* msg)
{   
    switch(type)
    {
        default:
            fprintf(stderr, "[Error] %s\n", msg);
    }
}