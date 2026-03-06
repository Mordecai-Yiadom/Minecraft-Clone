#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_H

#include <pthread.h>
#include <stdbool.h>
#include "frontend/frontend.h"
#include "renderpass.h"
#include "../../core/queue.h"

#define DELTA_TIME() RenderSystem_deltaTime()
#define FPS() RenderSystem_fps()

#define FPS_ULIMITED INTMAX

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

typedef struct RenderSystemProps
{
    u64 commandQueueLength;
    int targetFPS;
}RenderSystemProps;


//Holds state for the Minecraft Client RenderSystem
typedef struct RenderSystem
{   
    ArrayList renderPasses;
    float deltaTime;
    int fps;
    int targetFPS;
    bool isInitialized;
}RenderSystem;

#ifdef MINECRAFT_CLIENT_RENDER_SYSTEM_C
    //Global state for Minecraft Client RenderSystem 
    static RenderSystem RENDERSYSTEM_STATE;

    //Recalculates RenderSystem's delta time. This is done after every frame is completes
    static inline void RenderSystem_updateDeltaTime();

    //Recalculates RenderSystem's fps. This is done after every frame is completes
    static inline void RenderSystem_updateFPS();

    static inline void RenderSystem_beginFrame();

    static inline void RenderSystem_endFrame();

    static inline void RenderSystem_executePasses();
#endif


//Initalizes the global state for the RenderSystem other related utilities.
void RenderSystem_init();

//De-initializes and clears the global state for the RenderSystem and other relate utilites
void RenderSystem_shutdown();

/* 
    Checks whether the RenderSystem and its global state has been initialized.
    @return true or false
*/
bool RenderSystem_isInitialized();

/*
    Reads the current scene data for the RenderSystem global state and begins renderpasses to draw next frame
*/
void RenderSystem_update();


void RenderSystem_addRenderPass(RenderPass renderPass);

void RenderSystem_removeRenderPass();

///FOR TESTING ONLY
void* RenderSystem_getRenderPass(int index);

/*
    Gets the current delta time for the RenderSystem global state
    @returns deltaTime > 0
*/
float RenderSystem_deltaTime();


/*
    Sets the target fps for the RenderSystem's global state
    @param targetFPS fps for RenderSystem to target when rendering frames. 
    Does not accept negative numbers. 
    FPS_UNLIMITED may be used to remove the targetFPS and allow the RenderSystem to render as fast as possible
    
*/
void RenderSystem_setTargetFPS(int targetFPS);


/*
    Gets the current frames per second (fps) for the RenderSystem global state
    @returns fps >= 0
*/
int RenderSystem_fps();




#endif