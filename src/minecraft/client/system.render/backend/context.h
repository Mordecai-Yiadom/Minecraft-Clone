#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_CONTEXT_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_CONTEXT_H

#include <glad/glad.h>

typedef enum RenderAPI
{
    OPENGL_CORE,
    OPENGL_ES,
}RenderAPI;

typedef struct RenderContext
{
    RenderAPI api;
    unsigned int versionMajor;
    unsigned int versionMinor;
}RenderContext;

void RenderSystem_initRenderContext(RenderContext *context);

#endif