#ifndef MINECRAFT_CLIENT_GAME_CLIENTCHUNK_H
#define MINECRAFT_CLIENT_GAME_CLIENTCHUNK_H

#include "../../../core/core.h"


#include "../block/blockmesh.h"

#include "../../system.render/backend/mesh.h"

typedef struct ChunkMeshBuildingData
{
    BlockFace *vertexBuffer;
    int vertexBufferLength;
    int *indexBuffer;

    int topRightIndex;
    int topLeftIndex;
    int bottomLeftIndex;
    int bottomRightIndex;


    int indexBufferLength;
}ChunkMeshBuildingData;

typedef struct ChunkMesh
{
    Mesh mesh;
    Chunk *chunk;
    ChunkMeshBuildingData buildingData;
}ChunkMesh;


#define IS_VALID_DIMENSION(d) ((bool) d.xLen > 0 || d.yLen > 0 || d.zLen > 0)

ChunkMesh ChunkMesh_create(Chunk *chunk);

void ChunkMesh_destroy(ChunkMesh *chunkMesh);

//Builds a given ChunkMesh's vertex and index data based on its current chunk's data;
void ChunkMesh_build(ChunkMesh *chunkMesh);

//Writes a given ChunkMesh's RAM data to GPU memory 
void ChunkMesh_flush(ChunkMesh *chunkMesh);

void ChunkMesh_addBlock(ChunkMesh *chunkMesh, Block block, ChunkBlockPosition chunkBlockPosition);

bool ChunkMesh_isValid(ChunkMesh *chunkMesh);

// Resets a given ChunkMesh's vertex and index building data
void ChunkMesh_clear(ChunkMesh *chunkMesh);





#endif