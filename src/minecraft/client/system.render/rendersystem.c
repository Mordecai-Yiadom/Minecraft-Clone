#include "frontend/window.h"
#include "backend/backend.h"

#define MINECRAFT_CLIENT_RENDER_SYSTEM_C
#include "rendersystem.h"



void RenderSystem_init()
{   
    if(RenderSystem_isInitialized())
    {
        Logger_logError(RENDER_SYSTEM, "RenderSystem is already initialized.");
        return;
    }

    if(!glfwInit())
    {
        Logger_logError(RENDER_SYSTEM, "GLFW failed to initialize.");
        return;
    }

    RENDERSYSTEM_STATE.renderPasses = ArrayList_create(5, sizeof(RenderPass), DYNAMIC_MEMORY);
    RENDERSYSTEM_STATE.isInitialized = true;
}

void RenderSystem_shutdown()
{
    glfwTerminate();
    ArrayList_destroy(&RENDERSYSTEM_STATE.renderPasses);
    memset(&RENDERSYSTEM_STATE, 0, sizeof(RenderSystem));
}

void RenderSystem_beginFrame()
{}

void RenderSystem_endFrame()
{}


bool RenderSystem_isInitialized()
{
    return RENDERSYSTEM_STATE.isInitialized;
}

void RenderSystem_endRenderPass(Window *window)
{   
    Window_swapBuffers(window);

    RenderSystem_updateDeltaTime();
    RenderSystem_updateFPS();
}




float RenderSystem_deltaTime()
{
    return RENDERSYSTEM_STATE.deltaTime;
}


void RenderSystem_setTargetFPS(int targetFPS)
{   
    if(targetFPS > -1) 
        RENDERSYSTEM_STATE.targetFPS = targetFPS;
}

int RenderSystem_fps()
{
    return RENDERSYSTEM_STATE.fps;
}

static inline void RenderSystem_updateDeltaTime()
{   
    static float currentFrameTime = 0;
    static float lastFrameTime = 0;

    currentFrameTime = glfwGetTime();
    RENDERSYSTEM_STATE.deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
}

static inline void RenderSystem_updateFPS()
{   
    static int currentFrameCount = 0;
    static int lastSampledFrame = 0;
    if((glfwGetTime() - lastSampledFrame) < 1) ++currentFrameCount;
    else 
    {
        RENDERSYSTEM_STATE.fps = currentFrameCount;
        currentFrameCount = 0;
        lastSampledFrame = glfwGetTime();
    }
}