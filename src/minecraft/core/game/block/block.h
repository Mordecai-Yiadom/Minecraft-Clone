#ifndef MINECRAFT_CORE_GAME_BLOCK_H
#define MINECRAFT_CORE_GAME_BLOCK_H

#include "../../util/memtypes.h"

typedef u32 BlockID;

typedef struct Block
{
    BlockID id;
}Block;

typedef enum BlockType
{
    AIR = 0,
    GRASS = 1,
    DIRT = 2,
    STONE = 3,
}BlockType;


#endif