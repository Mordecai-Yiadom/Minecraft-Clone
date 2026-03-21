#ifndef MINECRAFT_CORE_GAME_CHUNK_H
#define MINECRAFT_CORE_GAME_CHUNK_H

#define CHUNK_X_LIMIT 16
#define CHUNK_Y_LIMIT 5
#define CHUNK_Z_LIMIT 16

#include "../../util/memtypes.h"

#include "../block/block.h"

typedef struct ChunkIndex
{
    int xOffset;
    int zOffset
}ChunkIndex;

typedef struct ChunkPosition
{   
    ChunkIndex chunkIndex;
    float x;
    float y;
    float z;
}ChunkPosition;

typedef struct ChunkBlockPosition
{   
    ChunkIndex chunkIndex;
    int x;
    int y;
    int z;
}ChunkBlockPosition;

typedef struct Chunk
{   
    void *world;
    BlockType blocks[CHUNK_X_LIMIT][CHUNK_Y_LIMIT][CHUNK_Z_LIMIT];
    ChunkIndex index;
}Chunk;

#define CHUNKINDEX(x, z) ((ChunkIndex){.xOffset=(x), .zOffset=(z)})
#define CHUNKPOS(i, xp, yp, zp) ((ChunkPosition){.chunkIndex=(i), .x=(xp), .y=(yp), .z=(zp)})
#define CHUNKBLOCKPOS(i, xp, yp, zp) ((ChunkBlockPosition){.chunkIndex=(i), .x=(xp), .y=(yp), .z=(zp)})

Chunk* Chunk_create(void *world, ChunkIndex index);

bool Chunk_isValidBlockOffset(int xOffset, int yOffset, int zOffset);

bool ChunkPosition_isValid(ChunkPosition position);

bool ChunkBlockPosition_isValid(ChunkBlockPosition position);



#endif