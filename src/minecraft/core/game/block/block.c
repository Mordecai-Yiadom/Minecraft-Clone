#include "block.h"

bool BlockType_isVisible(BlockType blockType)
{
    switch(blockType)
    {
        case AIR:
        case VOID_AIR:
            return false;
        default:
            return true;
    }

    return true;
}

bool BlockType_isSolid(BlockType blockType)
{
    switch(blockType)
    {
        case DIRT:
        case STONE:
        case GRASS:
        case BEDROCK:
            return true;
        default:
            return false;
    }

    return true;
}