#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_H

#include <pthread.h>
#include <stdbool.h>
#include "frontend/frontend.h"

#define DELTA_TIME() RenderSystem_deltaTime()
#define FPS() RenderSystem_fps()

typedef enum RenderSystemError
{   
    NO_ERROR,
    SHADER_ERROR,
    CONTEXT_CREATION_ERROR,
}RenderSystemError;

typedef struct RenderBatch
{
    Array array;
}RenderBatch;

typedef struct RenderSystem
{   
    pthread_t renderThread;
    bool calcFPS;
    bool isInitialized;
}RenderSystem;

#ifdef MINECRAFT_CLIENT_RENDER_SYSTEM_C
    static RenderSystem RENDERSYSTEM_STATE;

    static void 
#endif


void RenderSystem_init();

void RenderSystem_terminate();

void RenderSystem_startRenderPass();

void RenderSystem_queueRenderBatch(RenderBatch batch);

void RenderSystem_endRenderPass(Window *window);

float RenderSystem_deltaTime();

int RenderSystem_fps();




#endif