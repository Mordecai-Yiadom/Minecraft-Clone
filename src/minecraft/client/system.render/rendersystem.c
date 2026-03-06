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

    RenderPipeline pipeline;
    RenderTarget target;
    RenderPass quadPass = RenderPass_create("quad-test", pipeline, target);
    RenderSystem_addRenderPass(quadPass);
    puts("[RenderSystem] RenderSystem has been initialized.");
}

void RenderSystem_shutdown()
{
    glfwTerminate();
    ArrayList_destroy(&RENDERSYSTEM_STATE.renderPasses);
    memset(&RENDERSYSTEM_STATE, 0, sizeof(RenderSystem));
}


void RenderSystem_update()
{   
    static int frameCount = 1;
    RenderSystem_beginFrame();
    RenderSystem_endFrame();
    printf("[RenderSystem] frame {%d} complete.\n", frameCount);
    frameCount++;
}

void RenderSystem_addRenderPass(RenderPass renderPass)
{
    ArrayList_add(&RENDERSYSTEM_STATE.renderPasses, (byte*)&renderPass);
}

void* RenderSystem_getRenderPass(int index)
{
    return ArrayList_getAddress(&RENDERSYSTEM_STATE.renderPasses, index);
}



bool RenderSystem_isInitialized()
{
    return RENDERSYSTEM_STATE.isInitialized;
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


static inline void RenderSystem_beginFrame()
{
    RenderSystem_executePasses();
}

static inline void RenderSystem_endFrame()
{   
    RenderSystem_updateDeltaTime();
    RenderSystem_updateFPS();
}

static inline void RenderSystem_executePasses()
{   
    int length = ArrayList_length(&RENDERSYSTEM_STATE.renderPasses);
    RenderPass currPass;
    for(int i = 0; i < length; i++)
    {
        ArrayList_get(&RENDERSYSTEM_STATE.renderPasses, i, (byte*)&currPass);
        RenderPass_execute(&currPass);
    }
}
