#include "logger.h"

void Logger_logError(ErrorType type, char* msg)
{
    fprintf(stderr, "[Error] %s\n", msg);
}