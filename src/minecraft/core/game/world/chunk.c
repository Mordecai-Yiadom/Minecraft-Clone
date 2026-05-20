#include "chunk.h"

#include <string.h>
#include "../block/block.h"
#include <stdlib.h>

Chunk* Chunk_create(void* world, ChunkIndex index)
{   
    if(!world) return NULL;

    Chunk *chunk = calloc(1, sizeof(Chunk));

    chunk->world = world;
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
            // chunk->blocks[x][0][z] = STONE;
        }
    }
    chunk->blocks[9][7][6] = DIAMOND_ORE;
    chunk->blocks[4][4][5] = DIAMOND_ORE;
    chunk->blocks[4][5][5] = LEAVES;
    
    return chunk;
}

ChunkBlockPosition ChunkPosition_toBlockPosition(ChunkPosition position)
{
    return CHUNKBLOCKPOS(position.chunkIndex, 
        (int)position.x, (int)position.y, (int)position.z);
}

ChunkPosition ChunkBlockPosition_toChunkPosition(ChunkBlockPosition position)
{
    return CHUNKPOS(position.chunkIndex, 
        (float)position.x, (float)position.y, (float)position.z);
}

ChunkPosition ChunkPosition_floor(ChunkPosition position)
{
    return CHUNKPOS(position.chunkIndex, 
        floorf(position.x), floorf(position.y), floorf(position.z));
}

ChunkPosition ChunkPosition_ceiling(ChunkPosition position)
{
    return CHUNKPOS(position.chunkIndex, 
        ceilf(position.x), ceilf(position.y), ceilf(position.z));
}




bool ChunkPosition_isValid(ChunkPosition position)
{
    return (position.x >= 0.f && position.x < CHUNK_X_LIMIT) 
    && (position.y >= 0.f && position.y < CHUNK_Y_LIMIT) 
    && (position.z >= 0.f && position.z < CHUNK_Z_LIMIT);
}

bool ChunkBlockPosition_isValid(ChunkBlockPosition position)
{
    return (position.x > -1 && position.x < CHUNK_X_LIMIT) 
    && (position.y > -1 && position.y < CHUNK_Y_LIMIT) 
    && (position.z > -1 && position.z < CHUNK_Z_LIMIT)
    && position.chunkIndex.xOffset != CHUNKINDEX_NULL.xOffset
    && position.chunkIndex.zOffset != CHUNKINDEX_NULL.zOffset;
}


void Chunk_setBlockAt(Chunk* chunk, ChunkPosition position, Block block)
{
    if(!chunk || !ChunkPosition_isValid(position) || !Block_isValid(block)) return;
    ChunkBlockPosition blockPos = ChunkPosition_toBlockPosition(position);
    chunk->blocks[blockPos.x][blockPos.y][blockPos.z] = block.id;
}

Block Chunk_getBlockAt(Chunk* chunk, ChunkPosition position)
{
    if(!chunk || !ChunkPosition_isValid(position)) return BLOCK_NULL;
    
    ChunkBlockPosition blockPos = ChunkPosition_toBlockPosition(position);
    Block block = {.id=chunk->blocks[blockPos.x][blockPos.y][blockPos.z]};
    return block;
}