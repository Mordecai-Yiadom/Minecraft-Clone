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
    UNKNOWN,
}BlockType;

typedef struct BlockState
{
    float percentageBroken;
    u32 lightLevel;
}BlockState;

typedef struct Block
{
    BlockType id;
    BlockState state;
}Block;





bool BlockType_isVisible(BlockType blockType);
bool BlockType_isSolid(BlockType blockType);


#endif