#ifndef MINECRAFT_CLIENT_CHUNKRENDERER_H
#define MINECRAFT_CLIENT_CHUNKRENDERER_H

#include "../renderer.h"
#include "../renderpass.h"

#include "../../game/world/chunkmesh.h"

typedef struct ChunkRenderer
{
    RenderPass *renderpass;
}ChunkRenderer;


#ifdef MINECRAFT_CLIENT_CHUNKRENDERER_C
static bool isInitialized = false;
static inline void ChunkRenderer_create();
static inline void ChunkRenderer_destroy();
static ChunkRenderer INSTANCE;
#endif

void ChunkRenderer_init();

void ChunkRenderer_drawChunkMesh(ChunkMesh *chunkMesh);

Camera* ChunkRenderer_getRenderTargetCamera();


#endif