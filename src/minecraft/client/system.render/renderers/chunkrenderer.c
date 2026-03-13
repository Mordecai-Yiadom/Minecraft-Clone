#define MINECRAFT_CLIENT_CHUNKRENDERER_C
#include "chunkrenderer.h"
#include "../pipelines/genericpipeline.h"
#include "../renderpasses/chunkrenderpass.h"
#include "../rendersystem.h"

static inline void ChunkRenderer_create()
{
    if(isInitialized) return;
    //Create renderpass
    
    RenderSystem_addRenderPass(ChunkRenderPass_create());
    
    INSTANCE.renderpass = RenderSystem_getRenderPass(CHUNKRENDERPASS_INDEX);
    isInitialized = true;
    
}

static inline void ChunkRenderer_destroy()
{
    if(!isInitialized) return;
    RenderPass_destory(INSTANCE.renderpass);
    memset(&INSTANCE, 0, sizeof(ChunkRenderer));
    isInitialized = false;
}

void ChunkRenderer_init()
{   
    
    if(isInitialized) return;
    ChunkRenderer_create();
    puts("ChunkRenderer created");
}


void ChunkRenderer_drawChunkMesh()
{
    Quad_draw();
}





