#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_CONTEXT_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_CONTEXT_H

#include <glad/glad.h>

#ifndef RENDER_SYSTEM_SHARED_CONTEXT_LIMIT
    #define RENDER_SYSTEM_SHARED_CONTEXT_LIMIT 8
#endif

typedef enum GraphicsAPI
{
    OPENGL_CORE,
    OPENGL_ES,
}GraphicsAPI;

typedef struct RenderContext
{   
    unsigned int versionMajor;
    unsigned int versionMinor;
    GraphicsAPI graphicsAPI;
}RenderContext;

RenderContext* RenderContext_createOpenGLContext(GraphicsAPI renderAPI, unsigned int versionMajor, unsigned int versionMinor);


#endif