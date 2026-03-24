#include "block.h"



bool Block_isTransparent(Block block)
{
    switch(block.id)
    {
        case AIR:
        case VOID_AIR:
        case LEAVES:
        case BLOCKID_INVALID:
            return true;
        default:
            return false;
    }

    return false;
}


bool Block_isAir(Block block)
{
    switch(block.id)
    {
        case AIR:
        case VOID_AIR:
            return true;
        default:
            return false;
    }
    return false;
}

bool Block_isValid(Block block)
{
    return block.id != BLOCKID_INVALID;
}