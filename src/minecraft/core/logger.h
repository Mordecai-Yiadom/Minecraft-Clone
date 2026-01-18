#ifndef MINECRAFT_CORE_LOGGER_H
#define MINECRAFT_CORE_LOGGER_H

#include "core.h"

typedef enum ErrorType
{
    FILE_IO,
    RENDER_SYSTEM,
    AUDIO_SYSTEM,
    GAME_SIMULATION_ERROR,
    APPLICATION_ERROR,
}ErrorType;

void Logger_logError(ErrorType type, char* msg);

#endif