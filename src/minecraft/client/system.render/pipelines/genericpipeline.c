
#define MINECRAFT_CLIENT_GENERICPIPELINE_C
#include "genericpipeline.h"
#include "../../../core/core.h"



RenderPipeline GenericPipeline_create()
{   

    Shader shader = Shader_create("assets/minecraft/shaders/default.vs", NULL, "assets/minecraft/shaders/default.fs");
    
    if(!Shader_isValid(shader)) Logger_logError(RENDER_SYSTEM, "Shader Program handle is invalid.");
    RenderPipeline pipeline = RenderPipeline_create(shader, GenericPipeline_load, GenericPipeline_unload);
    return pipeline;
}




static inline void GenericPipeline_load(RenderPipeline *pipeline, RenderTarget *renderTarget)
{   
    if(!pipeline || !renderTarget) return;

    Renderer_setClearColor(COLOR_RGB(66, 206, 245));
    Renderer_clearBuffer(COLOR_BUFFER);

    Renderer_clearBuffer(DEPTH_BUFFER);
    Renderer_enableTest(DEPTH_TEST);
    
    Color quadColor = COLOR_RGB(222, 69, 201);
    Shader_setFloat(pipeline->shader, "r", quadColor.red);
    Shader_setFloat(pipeline->shader, "g", quadColor.green);
    Shader_setFloat(pipeline->shader, "b", quadColor.blue);

    //Camera_setFov(&camera, 100 * sin(glfwGetTime()));
    Transform3D quad1Transform;
   
    // vec3f(quad1Transform.position, 10 * sin(glfwGetTime()), 0, 10 * cos(glfwGetTime()));
    vec3f(quad1Transform.position, 0, 0, 10);

    glm_mat4_identity(quad1Transform.matrix);
    glm_translate(quad1Transform.matrix, quad1Transform.position);
    
    Camera_updateViewMatrix(&renderTarget->camera);
    
    Shader_setMat4x4f(pipeline->shader, "projection", renderTarget->camera.matrix.projection);
    Shader_setMat4x4f(pipeline->shader, "view", renderTarget->camera.matrix.view);
    Shader_setMat4x4f(pipeline->shader, "model", quad1Transform.matrix);

    
}

static inline void GenericPipeline_unload(RenderPipeline *pipeline, RenderTarget *renderTarget)
{
    if(!pipeline || !renderTarget) return;

    Renderer_disableTest(DEPTH_TEST);
}