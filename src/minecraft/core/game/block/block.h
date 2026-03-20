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


bool BlockType_isVisible(BlockType blockType);
bool BlockType_isSolid(BlockType blockType);


#endif