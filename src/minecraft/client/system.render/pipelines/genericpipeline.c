
#define MINECRAFT_CLIENT_GENERICPIPELINE_C
#include "genericpipeline.h"
#include "../../../core/core.h"

static Texture2D dirtTexture;

RenderPipeline GenericPipeline_create()
{   

    Shader shader = Shader_create("assets/minecraft/shaders/default.vs", NULL, "assets/minecraft/shaders/default.fs");
    
    if(!Shader_isValid(shader)) Logger_logError(RENDER_SYSTEM, "Shader Program handle is invalid.");
    RenderPipeline pipeline = RenderPipeline_create(shader, GenericPipeline_load, GenericPipeline_unload);

    dirtTexture = Texture2D_create("assets/minecraft/textures/blocks/dirt.png");
    printf("Dirt Texture: %d\n", dirtTexture.samplerID);

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

    Transform3D chunkTransform;
    vec3f(chunkTransform.position, 0, 0, 0);
    glm_mat4_identity(chunkTransform.matrix);
    glm_translate(chunkTransform.matrix, chunkTransform.position);
    
    Camera_updateViewMatrix(&renderTarget->camera);
    
    Shader_setMat4x4f(pipeline->shader, "projection", renderTarget->camera.matrix.projection);
    Shader_setMat4x4f(pipeline->shader, "view", renderTarget->camera.matrix.view);
    Shader_setMat4x4f(pipeline->shader, "model", chunkTransform.matrix);

    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, dirtTexture.id);

    // ivec4 textureIDs = {0, 1, 2, 3};
    Shader_setInt(pipeline->shader, "textureID", 0);
    
}

static inline void GenericPipeline_unload(RenderPipeline *pipeline, RenderTarget *renderTarget)
{
    if(!pipeline || !renderTarget) return;

    Renderer_disableTest(DEPTH_TEST);
}