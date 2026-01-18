#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_H

#include <stdbool.h>
#include "frontend/window.h"

#define DELTA_TIME() RenderSystem_getDeltaTime()
#define FPS() RenderSystem_getFPS()

typedef enum RenderSystemError
{   
    NO_ERROR,
    SHADER_ERROR,
    CONTEXT_CREATION_ERROR,
}RenderSystemError;

typedef struct RenderSystemInfo
{
    int frameCap;
}RenderSystemInfo;

typedef struct RenderSystem
{   
    bool calcFPS;
    void* renderQueue;
}RenderSystem;


void RenderSystem_init();

void RenderSystem_terminate();

void RenderSystem_startRenderPass();

void RenderSystem_endRenderPass(Window *window);

float RenderSystem_getDeltaTime();

int RenderSystem_getFPS();



#endif