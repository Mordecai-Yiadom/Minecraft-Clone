#ifndef MINECRAFT_CORE_LOGGER_H
#define MINECRAFT_CORE_LOGGER_H


typedef enum ErrorType
{
    FILE_IO,
    RENDER_SYSTEM,
    AUDIO_SYSTEM,
    GAME_SIMULATION_ERROR,
}ErrorType;

void Logger_logError(ErrorType type, char* msg);

#endif