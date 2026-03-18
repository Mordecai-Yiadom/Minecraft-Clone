#include "clientchunk.h"
#include <string.h>

#define DEFAULT_CHUNK_VERTEXBUFFER_SIZE (sizeof(BlockMesh) * CHUNK_X_LIMIT * CHUNK_Y_LIMIT * CHUNK_Z_LIMIT)
#define DEFAULT_CHUNK_INDEXBUFFER_SIZE (sizeof(int)  * 36 * CHUNK_X_LIMIT * CHUNK_Y_LIMIT * CHUNK_Z_LIMIT)

#include "../../system.render/backend/backend.h"

#include <stdio.h>

ChunkMesh ChunkMesh_create(Chunk *chunk)
{   
    ChunkMesh chunkMesh;
    memset(&chunkMesh, 0, sizeof(ChunkMesh));
    if(!chunk) return chunkMesh;
    
    MeshData meshData;
    meshData.format = POS3f_NORM3f_UV2f_TEXID1i;
    meshData.type = DYNAMIC;
    meshData.vertexData = (BufferData){.buffer=NULL, .size=DEFAULT_CHUNK_VERTEXBUFFER_SIZE};
    meshData.indexData = (BufferData){.buffer=NULL, .size=DEFAULT_CHUNK_INDEXBUFFER_SIZE};

    chunkMesh.mesh = Mesh_create(meshData);
    chunkMesh.chunk = chunk;

    return chunkMesh;
}


void ChunkMesh_build(ChunkMesh *mesh)
{   
    BlockFace *chunkMeshBuffer = calloc((CHUNK_X_LIMIT * CHUNK_Y_LIMIT * CHUNK_Z_LIMIT * 6), sizeof(BlockFace));
    int *indexBuffer = calloc((CHUNK_X_LIMIT * CHUNK_Y_LIMIT * CHUNK_Z_LIMIT * 36), sizeof(int));

    int topRightIndex = 0;
    int topLeftIndex = 1;
    int bottomLeftIndex = 2;
    int bottomRightIndex = 3;

    int indexBufferLength = 0;

    if(!mesh) return;
    int i = 0;
    for(int x = 0; x < CHUNK_X_LIMIT; x++)
    {
        for(int y = 0; y < CHUNK_Y_LIMIT; y++)
        {
            for(int z = 0; z < CHUNK_Z_LIMIT; z++)
            {   
                vec3 translation = {(float)x, (float)y, (float)z};

                BlockFace north = BlockMesh_getFace(mesh->chunk->blocks[x][y][z], BLOCKFACE_NORTH);
                BlockFace_translate(&north, translation);
                chunkMeshBuffer[i++] = north;
                indexBuffer[indexBufferLength++] = topRightIndex;
                indexBuffer[indexBufferLength++] = topLeftIndex;
                indexBuffer[indexBufferLength++] = bottomRightIndex;

                indexBuffer[indexBufferLength++] = topLeftIndex;
                indexBuffer[indexBufferLength++] = bottomLeftIndex;
                indexBuffer[indexBufferLength++] = bottomRightIndex;

                // printf("topRightIndex: %d\n", topRightIndex);
                // printf("topLeftIndex: %d\n", topLeftIndex);
                // printf("bottomLeftIndex: %d\n", bottomLeftIndex);
                // printf("bottomRightIndex: %d\n\n", bottomRightIndex);

                topRightIndex += 4;
                topLeftIndex += 4;
                bottomLeftIndex += 4;
                bottomRightIndex += 4;

  

                BlockFace south = BlockMesh_getFace(mesh->chunk->blocks[x][y][z], BLOCKFACE_SOUTH);
                BlockFace_translate(&south, translation);
                chunkMeshBuffer[i++] = south;
                indexBuffer[indexBufferLength++] = topRightIndex;
                indexBuffer[indexBufferLength++] = topLeftIndex;
                indexBuffer[indexBufferLength++] = bottomRightIndex;

                indexBuffer[indexBufferLength++] = topLeftIndex;
                indexBuffer[indexBufferLength++] = bottomLeftIndex;
                indexBuffer[indexBufferLength++] = bottomRightIndex;

                topRightIndex += 4;
                topLeftIndex += 4;
                bottomLeftIndex += 4;
                bottomRightIndex += 4;


                BlockFace east = BlockMesh_getFace(mesh->chunk->blocks[x][y][z], BLOCKFACE_EAST);
                BlockFace_translate(&east, translation);
                chunkMeshBuffer[i++] = east;
                indexBuffer[indexBufferLength++] = topRightIndex;
                indexBuffer[indexBufferLength++] = topLeftIndex;
                indexBuffer[indexBufferLength++] = bottomRightIndex;

                indexBuffer[indexBufferLength++] = topLeftIndex;
                indexBuffer[indexBufferLength++] = bottomLeftIndex;
                indexBuffer[indexBufferLength++] = bottomRightIndex;

                topRightIndex += 4;
                topLeftIndex += 4;
                bottomLeftIndex += 4;
                bottomRightIndex += 4;


                BlockFace west = BlockMesh_getFace(mesh->chunk->blocks[x][y][z], BLOCKFACE_WEST);
                BlockFace_translate(&west, translation);
                chunkMeshBuffer[i++] = west;
                indexBuffer[indexBufferLength++] = topRightIndex;
                indexBuffer[indexBufferLength++] = topLeftIndex;
                indexBuffer[indexBufferLength++] = bottomRightIndex;

                indexBuffer[indexBufferLength++] = topLeftIndex;
                indexBuffer[indexBufferLength++] = bottomLeftIndex;
                indexBuffer[indexBufferLength++] = bottomRightIndex;

                topRightIndex += 4;
                topLeftIndex += 4;
                bottomLeftIndex += 4;
                bottomRightIndex += 4;


                BlockFace top = BlockMesh_getFace(mesh->chunk->blocks[x][y][z], BLOCKFACE_TOP);
                BlockFace_translate(&top, translation);
                chunkMeshBuffer[i++] = top;
                indexBuffer[indexBufferLength++] = topRightIndex;
                indexBuffer[indexBufferLength++] = topLeftIndex;
                indexBuffer[indexBufferLength++] = bottomRightIndex;

                indexBuffer[indexBufferLength++] = topLeftIndex;
                indexBuffer[indexBufferLength++] = bottomLeftIndex;
                indexBuffer[indexBufferLength++] = bottomRightIndex;

                topRightIndex += 4;
                topLeftIndex += 4;
                bottomLeftIndex += 4;
                bottomRightIndex += 4;


                BlockFace bottom = BlockMesh_getFace(mesh->chunk->blocks[x][y][z], BLOCKFACE_BOTTOM);
                BlockFace_translate(&bottom, translation);
                chunkMeshBuffer[i++] = bottom;
                indexBuffer[indexBufferLength++] = topRightIndex;
                indexBuffer[indexBufferLength++] = topLeftIndex;
                indexBuffer[indexBufferLength++] = bottomRightIndex;

                indexBuffer[indexBufferLength++] = topLeftIndex;
                indexBuffer[indexBufferLength++] = bottomLeftIndex;
                indexBuffer[indexBufferLength++] = bottomRightIndex;

                topRightIndex += 4;
                topLeftIndex += 4;
                bottomLeftIndex += 4;
                bottomRightIndex += 4;
            }
        }
    }

    BufferData data = {.buffer=chunkMeshBuffer, .size=VertexBuffer_getSize(&mesh->mesh.vbo)};
    VertexBuffer_write(&mesh->mesh.vbo, data, 0);

    BufferData indexBufferData = {.buffer=indexBuffer, .size=(indexBufferLength * sizeof(int))};
    IndexBuffer_write(&mesh->mesh.ebo, indexBufferData, 0);
    printf("IndexBuffer Length: %d\n", indexBufferLength);
    free(chunkMeshBuffer);
    free(indexBuffer);
    
}


// void ChunkMesh_addBlock(ChunkMesh *chunkMesh, BlockMesh blockMesh, int xOffset, int yOffset, int zOffset)
// {
//     if(!chunkMesh || xOffset < 0 || yOffset < 0 || zOffset < 0) return;
    
    
//     VertexBuffer_write(&chunkMesh->mesh.vbo, );
// }
