#ifndef MINECRAFT_CLIENT_GAME_CLIENTCHUNK_H
#define MINECRAFT_CLIENT_GAME_CLIENTCHUNK_H

#include "../../../core/core.h"


#include "../block/clientblock.h"

#include "../../system.render/backend/mesh.h"

typedef struct ChunkMesh
{
    Mesh mesh;
    Chunk *chunk;
}ChunkMesh;


#define IS_VALID_DIMENSION(d) ((bool) d.xLen > 0 || d.yLen > 0 || d.zLen > 0)

ChunkMesh ChunkMesh_create(Chunk *chunk);

void ChunkMesh_build(ChunkMesh *mesh);

// void ChunkMesh_addBlock(ChunkMesh *chunkMesh, BlockMesh blockMesh, int xOffset, int yOffset, int zOffset);

bool ChunkMesh_isValid(ChunkMesh *chunkMesh);






#endif