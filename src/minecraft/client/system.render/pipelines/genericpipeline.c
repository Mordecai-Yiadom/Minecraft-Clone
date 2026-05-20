
#define MINECRAFT_CLIENT_GENERICPIPELINE_C
#include "genericpipeline.h"
#include "../../../core/core.h"

#include "../../game/block/blocktexture.h"
RenderPipeline GenericPipeline_create()
{   

    Shader shader = Shader_create("assets/minecraft/shaders/chunk/terrain.vs", NULL, "assets/minecraft/shaders/chunk/terrain.fs");
    
    if(!Shader_isValid(shader)) puts("Shader Program handle is invalid.");
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
    
    Renderer_enableMSAA();

    Transform3D chunkTransform;
    vec3f(chunkTransform.position, 0, 0, 0);
    glm_mat4_identity(chunkTransform.matrix);
    glm_translate(chunkTransform.matrix, chunkTransform.position);
    
    Camera_updateViewMatrix(&renderTarget->camera);
    
    Shader_setMat4x4f(pipeline->shader, "projection", renderTarget->camera.matrix.projection);
    Shader_setMat4x4f(pipeline->shader, "view", renderTarget->camera.matrix.view);
    Shader_setMat4x4f(pipeline->shader, "model", chunkTransform.matrix);

    BlockTextureManager_writeTexturesToShader(pipeline->shader);
    
}

static inline void GenericPipeline_unload(RenderPipeline *pipeline, RenderTarget *renderTarget)
{
    if(!pipeline || !renderTarget) return;

    Renderer_disableTest(DEPTH_TEST);
    Renderer_disableMSAA();
}