#ifndef MINECRAFT_CLIENT_RENDERCOMMNAD_H
#define MINECRAFT_CLIENT_RENDERCOMMNAD_H

#include "commands/drawcommand.h"

typedef enum RenderCommandType
{
    DRAW_ARRAYS,
    DRAW_INDEXED,
}RenderCommandType;


typedef void(*RenderCommandAddress)(void *args);

typedef struct RenderCommand
{   
    RenderCommandType type;
    RenderCommandAddress commandAddress;
    void *args;
}RenderCommand;

void RenderCommand_execute(RenderCommand command);




#endif