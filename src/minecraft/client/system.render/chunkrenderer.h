#include "renderer.h"

typedef struct ChunkMesh
{
    Mesh mesh;
}ChunkMesh;

typedef struct ChunkRenderer
{

}ChunkRenderer;

void ChunkRenderer_drawChunkMesh(ChunkMesh *chunkMesh);

ChunkMesh ChunkMesh_create();