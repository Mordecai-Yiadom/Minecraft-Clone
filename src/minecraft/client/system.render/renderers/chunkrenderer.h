#ifndef MINECRAFT_CLIENT_CHUNKRENDERER_H
#define MINECRAFT_CLIENT_CHUNKRENDERER_H

#include "../renderer.h"
#include "../renderpass.h"

typedef struct ChunkDimensions
{
    int xLen;
    int yLen;
    int zLen;
}ChunkDimensions;


typedef struct ChunkMesh
{   
    Mesh mesh;
    ChunkDimensions dimensions;
}ChunkMesh;

typedef struct ChunkRenderer
{
    RenderPass *renderpass;
}ChunkRenderer;


#define IS_VALID_DIMENSION(d) ((bool) d.xLen > 0 || d.yLen > 0 || d.zLen > 0)

#ifdef MINECRAFT_CLIENT_CHUNKRENDERER_C
static bool isInitialized = false;
static inline void ChunkRenderer_create();
static inline void ChunkRenderer_destroy();
static ChunkRenderer INSTANCE;
#endif

void ChunkRenderer_init();

void ChunkRenderer_drawChunkMesh(ChunkMesh *chunkMesh);

ChunkMesh ChunkMesh_create(ChunkDimensions dimensions);

bool ChunkMesh_isValid(ChunkMesh *chunkMesh);

#endif