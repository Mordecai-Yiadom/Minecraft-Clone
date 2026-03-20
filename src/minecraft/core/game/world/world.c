#define MINECRAFT_CORE_GAME_WORLD_C
#include "world.h"

#include <stdlib.h>
#include <string.h>


World* World_create(i64 seed)
{
    World *world = calloc(1, sizeof(World));
    world->seed = seed;

    world->chunk = Chunk_create(world);
    return world;
}


float* World_getDirectionVector(WorldDirection direction)
{
    switch(direction)
    {
        case WORLD_NORTH:
            return WORLD_NORTH_VECTOR;
        case WORLD_SOUTH: 
            return WORLD_SOUTH_VECTOR;
        case WORLD_EAST: 
            return WORLD_EAST_VECTOR;
        case WORLD_WEST: 
            return WORLD_WEST_VECTOR;
        case WORLD_UP: 
            return WORLD_UP_VECTOR;
        case WORLD_DOWN: 
            return WORLD_DOWN_VECTOR;
    }
    return NULL;
}


BlockPosition World_getBlockPosition(Chunk *chunk, int xOffset, int yOffset, int zOffset)
{
    if(!chunk) return (BlockPosition){.x=0, .y=0, .z=0};
    return (BlockPosition){.x=chunk->xOffset + xOffset, .y=yOffset, .z=chunk->zOffset + zOffset};
}


//NEED TO FIX NOW
BlockType World_getBlockAt(World *world, int x, int y, int z)
{
    if(!world || !Chunk_isValidBlockOffset(x, y, z)) return AIR;
    return world->chunk[0].blocks[x][y][z];
}