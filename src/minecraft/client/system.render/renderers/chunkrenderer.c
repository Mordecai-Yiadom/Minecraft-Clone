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


void ChunkRenderer_drawChunkMesh(ChunkMesh *chunkMesh)
{
    if(!chunkMesh) return;
    // Renderer_drawMesh(&chunkMesh->mesh);
    Quad_draw();
}

ChunkMesh ChunkMesh_create(ChunkDimensions dimensions)
{
    ChunkMesh chunkMesh;
    chunkMesh.dimensions = dimensions;

    // BufferData vboData = {.buffer=};
    // MeshData meshData;
    // meshData.format = POS3f_NORM3f_UV2f;
    // meshData.type = DYNAMIC;
    // meshData.indexData
    
    return chunkMesh;
}

bool ChunkMesh_isValid(ChunkMesh *chunkMesh)
{
    if(!chunkMesh) return false;
    return (Mesh_isValid(&chunkMesh->mesh) && IS_VALID_DIMENSION(chunkMesh->dimensions));
}

