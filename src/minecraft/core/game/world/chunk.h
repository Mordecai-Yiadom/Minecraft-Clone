#ifndef MINECRAFT_CORE_GAME_CHUNK_H
#define MINECRAFT_CORE_GAME_CHUNK_H

#define CHUNK_X_LIMIT 16
#define CHUNK_Y_LIMIT 5
#define CHUNK_Z_LIMIT 16

#include "../../util/memtypes.h"

#include "../block/block.h"



typedef struct Chunk
{   
    void *world;
    BlockType blocks[CHUNK_X_LIMIT][CHUNK_Y_LIMIT][CHUNK_Z_LIMIT];
    int xOffset;
    int zOffset;
}Chunk;

Chunk* Chunk_create(void *world);

bool Chunk_isValidBlockOffset(int xOffset, int yOffset, int zOffset);

#endif