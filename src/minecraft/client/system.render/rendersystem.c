#include "frontend/window.h"
#include "backend/backend.h"
#include "rendersystem.h"

static float RENDER_SYSTEM_DELTA_TIME = 0.0f;
static int RENDER_SYSEM_FPS = 0;

static float LAST_FRAME_TIME = 0.f;
static float CURRENT_FRAME_TIME = 0.f;

static inline void RenderSystem_updateDeltaTime();
static inline void RenderSystem_updateFPS();

static bool isInitialized = false;

static VertexBuffer vbo;
static VertexArray vao;
static Shader shader;

static float shapeVerts[] = 
{   
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  0,0,-1,     
    0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  0,0,-1,     
    0.5f, 0.5f, -0.5f,    1.0f, 1.0f, 0,0,-1,     
    0.5f, 0.5f, -0.5f,     1.0f, 1.0f, 0,0,-1,     
    -0.5f, 0.5f, -0.5f,    0.0f, 1.0f,  0,0,-1,     
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,   0,0,-1,    

};

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
    if(!isInitialized)
    {   
        BufferData data = {.buffer=&shapeVerts, .size=sizeof(shapeVerts)};

        printf("data.buffer=%p\n", data.buffer);
        printf("data.size=%lld\n", data.size);
        
        vbo = VertexBuffer_create(data, STATIC_DRAW);
        if(!VertexBuffer_isValid(vbo)) Logger_logError(RENDER_SYSTEM, "VBO handle is invalid.");
        

        
        printf("VBO handle: %d\n", vbo.id);
        printf("VBO size: %d\n",  VertexBuffer_getSize(vbo));
        
        vao = VertexArray_create();
        VertexArray_addAttribute(vao, vbo, POSITION_UVCOORD_NORMAL);

        shader = Shader_create("assets/shaders/default.vs", NULL, "assets/shaders/default.fs");

        if(!VertexArray_isArray(vao)) Logger_logError(RENDER_SYSTEM, "VAO handle is invalid.");
        if(!glIsProgram(shader.id)) Logger_logError(RENDER_SYSTEM, "Shader Program handle is invalid.");

        isInitialized = true;
    }

    glClearColor(sin(glfwGetTime()), cos(glfwGetTime()), sin(glfwGetTime()), 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    Shader_enable(shader);
    VertexArray_bind(vao);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
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