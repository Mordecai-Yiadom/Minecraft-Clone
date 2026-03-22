#include "chunkmesh.h"
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

    chunkMesh.buildingData.vertexBuffer = calloc((CHUNK_X_LIMIT * CHUNK_Y_LIMIT * CHUNK_Z_LIMIT * 6), sizeof(BlockFace));
    chunkMesh.buildingData.indexBuffer = calloc((CHUNK_X_LIMIT * CHUNK_Y_LIMIT * CHUNK_Z_LIMIT * 36), sizeof(int));

    chunkMesh.buildingData.topRightIndex = 0;
    chunkMesh.buildingData.topLeftIndex = 1;
    chunkMesh.buildingData.bottomLeftIndex = 2;
    chunkMesh.buildingData.bottomRightIndex = 3;

    chunkMesh.buildingData.indexBufferLength = 0;

    return chunkMesh;
}


void ChunkMesh_build(ChunkMesh *chunkMesh)
{   
    if(!chunkMesh) return;

    ChunkMesh_clear(chunkMesh);
    
    for(int x = 0; x < CHUNK_X_LIMIT; x++)
    {
        for(int y = 0; y < CHUNK_Y_LIMIT; y++)
        {
            for(int z = 0; z < CHUNK_Z_LIMIT; z++)
            {   
                ChunkMesh_addBlock(chunkMesh, 
                    BLOCK(chunkMesh->chunk->blocks[x][y][z]), 
                    CHUNKBLOCKPOS(chunkMesh->chunk->index, x, y, z));
            }
        }
    }
    //PUT HERE JUST FOR TESTING - REMOVE SOON
    ChunkMesh_flush(chunkMesh);    
}


void ChunkMesh_addBlock(ChunkMesh *chunkMesh, Block block, ChunkBlockPosition chunkBlockPosition)
{
    if(!chunkMesh || Block_isAir(block) || !ChunkBlockPosition_isValid(chunkBlockPosition)) return;

    vec3 meshTranslation = {((float)chunkBlockPosition.x) + chunkMesh->chunk->index.xOffset, 
        ((float)chunkBlockPosition.y), 
        ((float)chunkBlockPosition.z) + chunkMesh->chunk->index.zOffset};

    BlockFace currFace;
    for(BlockSide side = BLOCKFACE_NORTH; side < BLOCK_SIDE_COUNT; side++)
    {   
         
        float* faceDirectionVec = World_getDirectionVector((WorldDirection)side);
        if(!faceDirectionVec) puts("Null Face Direction Vector");

        WorldBlockPosition blockPos = ChunkBlockPosition_toWorldBlockPosition(chunkBlockPosition);

        WorldPosition neighborBlockPos = {vec3x(faceDirectionVec) + blockPos.x, 
            vec3y(faceDirectionVec) + blockPos.y, 
            vec3z(faceDirectionVec) + blockPos.z};
        
        
        // printf("NeighborBlock of (%d, %d, %d): (%.2f, %.2f, %.2f))\n",
        //     blockPos.x, blockPos.y, blockPos.z,
        //     neighborBlockPos.x, neighborBlockPos.y, neighborBlockPos.z);

        
        if(Block_isTransparent(World_getBlockAt(chunkMesh->chunk->world, neighborBlockPos)))
        {
            currFace = BlockMesh_getFace(Chunk_getBlockAt(chunkMesh->chunk, 
            ChunkBlockPosition_toChunkPosition(chunkBlockPosition)), side);

            BlockFace_translate(&currFace, meshTranslation);

            chunkMesh->buildingData.vertexBuffer[chunkMesh->buildingData.vertexBufferLength++] = currFace;
            chunkMesh->buildingData.indexBuffer[chunkMesh->buildingData.indexBufferLength++] = chunkMesh->buildingData.topRightIndex;
            chunkMesh->buildingData.indexBuffer[chunkMesh->buildingData.indexBufferLength++] = chunkMesh->buildingData.topLeftIndex;
            chunkMesh->buildingData.indexBuffer[chunkMesh->buildingData.indexBufferLength++] = chunkMesh->buildingData.bottomRightIndex;

            chunkMesh->buildingData.indexBuffer[chunkMesh->buildingData.indexBufferLength++] = chunkMesh->buildingData.topLeftIndex;
            chunkMesh->buildingData.indexBuffer[chunkMesh->buildingData.indexBufferLength++] = chunkMesh->buildingData.bottomLeftIndex;
            chunkMesh->buildingData.indexBuffer[chunkMesh->buildingData.indexBufferLength++] = chunkMesh->buildingData.bottomRightIndex;

            chunkMesh->buildingData.topRightIndex += 4;
            chunkMesh->buildingData.topLeftIndex += 4;
            chunkMesh->buildingData.bottomLeftIndex += 4;
            chunkMesh->buildingData.bottomRightIndex += 4;
        }    
        

    }
    
}


void ChunkMesh_flush(ChunkMesh *chunkMesh)
{
    if(!chunkMesh) return;
    BufferData vertexBufferData = {.buffer=chunkMesh->buildingData.vertexBuffer, .size=sizeof(BlockFace) * chunkMesh->buildingData.vertexBufferLength};
    VertexBuffer_write(&chunkMesh->mesh.vbo, vertexBufferData, 0);

    BufferData indexBufferData = {.buffer=chunkMesh->buildingData.indexBuffer, .size=(chunkMesh->buildingData.indexBufferLength * sizeof(int))};
    IndexBuffer_write(&chunkMesh->mesh.ebo, indexBufferData, 0);
    printf("IndexBuffer Length: %d\n", chunkMesh->buildingData.indexBufferLength);
}

void ChunkMesh_clear(ChunkMesh *chunkMesh)
{
    if(!chunkMesh) return;

    chunkMesh->buildingData.topRightIndex = 0;
    chunkMesh->buildingData.topLeftIndex = 1;
    chunkMesh->buildingData.bottomLeftIndex = 2;
    chunkMesh->buildingData.bottomRightIndex = 3;

    chunkMesh->buildingData.vertexBufferLength = 0;
    chunkMesh->buildingData.indexBufferLength = 0;
}
