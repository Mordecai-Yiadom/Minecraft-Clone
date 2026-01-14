#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_H

typedef enum RenderSystemError
{   
    NO_ERROR,
    SHADER_ERROR,
    CONTEXT_CREATION_ERROR,
}RenderSystemError;

typedef struct RenderSystem
{
    void* renderQueue;
}RenderSystem;

#endif