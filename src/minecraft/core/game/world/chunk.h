#ifndef MINECRAFT_CORE_GAME_CHUNK_H
#define MINECRAFT_CORE_GAME_CHUNK_H

#define CHUNK_X_LIMIT 16
#define CHUNK_Y_LIMIT 384
#define CHUNK_Z_LIMIT 16


#include "../block/block.h"

typedef struct ChunkIndex
{
    int xOffset;
    int zOffset;
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

//Convienience macro for quickly making a ChunkIndex struct
#define CHUNKINDEX(x, z) ((ChunkIndex){.xOffset=(x), .zOffset=(z)})

//Convienience macro for quickly making a ChunkPosition struct
#define CHUNKPOS(i, xp, yp, zp) ((ChunkPosition){.chunkIndex=(i), .x=(xp), .y=(yp), .z=(zp)})

//Convienience macro for quickly making a ChunkBlockPosition struct
#define CHUNKBLOCKPOS(i, xp, yp, zp) ((ChunkBlockPosition){.chunkIndex=(i), .x=(xp), .y=(yp), .z=(zp)})

#define CHUNKINDEX_NULL CHUNKINDEX(INT32_MAX, INT32_MAX)

Chunk* Chunk_create(void *world, ChunkIndex index);

void Chunk_destroy(Chunk* chunk);

ChunkBlockPosition ChunkPosition_toBlockPosition(ChunkPosition position);

ChunkPosition ChunkBlockPosition_toChunkPosition(ChunkBlockPosition position);

ChunkPosition ChunkPosition_floor(ChunkPosition position);

ChunkPosition ChunkPosition_ceiling(ChunkPosition position);

bool ChunkPosition_isValid(ChunkPosition position);

bool ChunkBlockPosition_isValid(ChunkBlockPosition position);


void Chunk_setBlockAt(Chunk* chunk, ChunkPosition position, Block block);

Block Chunk_getBlockAt(Chunk* chunk, ChunkPosition position);



#endif