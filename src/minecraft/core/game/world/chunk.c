#include "chunk.h"

#include <string.h>
#include "../block/block.h"
#include <stdlib.h>


Chunk* Chunk_create(void* world, ChunkIndex index)
{
    Chunk *chunk = calloc(1, sizeof(Chunk));

    chunk->world = world;
    chunk->index = index;
    chunk->index = index;
    
    //TESTING || REMOVE WHEN DONE
    int airLayer = 1;
    for(int x = 0; x < CHUNK_X_LIMIT; x++)
    {
        for(int z = 0; z < CHUNK_Z_LIMIT; z++)
        {
            chunk->blocks[x][airLayer][z] = STONE;
            chunk->blocks[x][4][z] = GRASS;
            chunk->blocks[x][3][z] = DIRT;
            chunk->blocks[x][2][z] = DIRT;
            chunk->blocks[x][0][z] = BEDROCK;
        }
    }

    return chunk;
}

bool ChunkPosition_isValid(ChunkPosition position)
{
    return (position.x > -1 && position.x < CHUNK_X_LIMIT) 
    && (position.y > -1 && position.y < CHUNK_Y_LIMIT) 
    && (position.z > -1 && position.z < CHUNK_Z_LIMIT);
}

bool ChunkBlockPosition_isValid(ChunkBlockPosition position)
{
    return (position.x > -1 && position.x < CHUNK_X_LIMIT) 
    && (position.y > -1 && position.y < CHUNK_Y_LIMIT) 
    && (position.z > -1 && position.z < CHUNK_Z_LIMIT);
}

bool Chunk_isValidBlockOffset(int xOffset, int yOffset, int zOffset)
{
    return (xOffset > -1 && xOffset < CHUNK_X_LIMIT) 
    && (yOffset > -1 && yOffset < CHUNK_Y_LIMIT) 
    && (zOffset > -1 && zOffset < CHUNK_Z_LIMIT);
}