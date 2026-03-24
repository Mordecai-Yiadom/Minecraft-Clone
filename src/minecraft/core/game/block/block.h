#ifndef MINECRAFT_CORE_GAME_BLOCK_H
#define MINECRAFT_CORE_GAME_BLOCK_H

#include "../../util/memtypes.h"
#include <stdbool.h>

typedef enum BlockType
{
    AIR,
    VOID_AIR,
    GRASS,
    DIRT,
    STONE,
    BEDROCK,
    DIAMOND_ORE,
    LEAVES,
    UNKNOWN,
    BLOCKID_INVALID = INT32_MAX
}BlockType;

typedef struct BlockState
{
    float percentageBroken;
    u32 lightLevel;
}BlockState;

typedef struct Block
{
    BlockType id;
}Block;

#define BLOCK_NULL ((Block){.id=(BLOCKID_INVALID)})

#define BLOCK(t) ((Block){.id=(t)})


bool Block_isTransparent(Block block);

bool Block_isAir(Block block);

//NOTE: A block is valid if block.id != BLOCKINVALID_ID 
bool Block_isValid(Block block);



#endif