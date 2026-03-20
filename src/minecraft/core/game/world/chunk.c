#include "chunk.h"

#include <string.h>
#include "../block/block.h"
#include <stdlib.h>


Chunk* Chunk_create(void* world)
{
    Chunk *chunk = calloc(1, sizeof(Chunk));
    chunk->xOffset = 0;
    chunk->zOffset = 0;
    chunk->world = world;
    //memset(chunk->blocks, DIRT, sizeof(chunk->blocks));
    
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

bool Chunk_isValidBlockOffset(int xOffset, int yOffset, int zOffset)
{
    return (xOffset > -1 && xOffset < CHUNK_X_LIMIT) 
    && (yOffset > -1 && yOffset < CHUNK_Y_LIMIT) 
    && (zOffset > -1 && zOffset < CHUNK_Z_LIMIT);
}