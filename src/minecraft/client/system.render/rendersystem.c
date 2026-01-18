#include "frontend/window.h"
#include "rendersystem.h"

static float RENDER_SYSTEM_DELTA_TIME = 0.0f;
static int RENDER_SYSEM_FPS = 0;

static float LAST_FRAME_TIME = 0.f;
static float CURRENT_FRAME_TIME = 0.f;

static inline void RenderSystem_updateDeltaTime();
static inline void RenderSystem_updateFPS();

void RenderSystem_init()
{
    if(!glfwInit())
    {
        Logger_logError(RENDER_SYSTEM, "GLFW failed to initialize.");
        return;
    }
}

void RenderSystem_terminate()
{
    glfwTerminate();
}

void RenderSystem_startRenderPass()
{
    glClearColor(sin(glfwGetTime()), cos(glfwGetTime()), sin(glfwGetTime()), 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RenderSystem_endRenderPass(Window *window)
{   
    Window_swapBuffers(window);

    RenderSystem_updateDeltaTime();
    RenderSystem_updateFPS();
}

float RenderSystem_getDeltaTime()
{
    return RENDER_SYSTEM_DELTA_TIME;
}

int RenderSystem_getFPS()
{
    return RENDER_SYSEM_FPS;
}

static inline void RenderSystem_updateDeltaTime()
{   
    CURRENT_FRAME_TIME = glfwGetTime();
    RENDER_SYSTEM_DELTA_TIME = CURRENT_FRAME_TIME - LAST_FRAME_TIME;
    LAST_FRAME_TIME = CURRENT_FRAME_TIME;
}

static inline void RenderSystem_updateFPS()
{   
    static int currentFrameCount = 0;
    static int lastSampledFrame = 0;
    if((glfwGetTime() - lastSampledFrame) < 1) ++currentFrameCount;
    else 
    {
        RENDER_SYSEM_FPS = currentFrameCount;
        currentFrameCount = 0;
        lastSampledFrame = glfwGetTime();
    }
}