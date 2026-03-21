#define MINECRAFT_CORE_GAME_WORLD_C
#include "world.h"

#include <stdlib.h>
#include <string.h>



World* World_create(i64 seed)
{
    World *world = calloc(1, sizeof(World));
    world->seed = seed;

    world->chunk = Chunk_create(world, CHUNKINDEX(0,0)); 
    return world;
}


void World_loadChunk(World *world, ChunkIndex chunkIndex)
{
    if(!world || World_isChunkLoaded(world, chunkIndex)) 
        return;

    Chunk *chunk = Chunk_create(&world, chunkIndex);
    if(chunk) ArrayList_add(&world->loadedChunks, &chunk);
}

void World_loadChunkAt(World *world, WorldPosition position)
{   
    World_loadChunk(world, World_getChunkIndexAt(world, position));
}

void World_unloadChunk(World *world, ChunkIndex chunkIndex);

void World_unloadChunkAt(World *world, WorldPosition position);

bool World_isChunkLoaded(World *world, ChunkIndex chunkIndex);

Chunk* World_getChunkAt(World *world, WorldPosition position);

Chunk* World_getChunkAtBlock(World *world, WorldBlockPosition position);

ChunkIndex World_getChunkIndexAt(World *world, WorldPosition position);

BlockType World_getBlockAt(World *world, WorldPosition position);

WorldPosition ChunkPosition_toWorldPosition(ChunkPosition position)
{
    return WORLDPOS(position.x + position.chunkIndex.xOffset, 
        position.y, 
        position.z + position.chunkIndex.zOffset);
}

ChunkPosition WorldPosition_toChunkPosition(WorldPosition position)
{   

    return CHUNKPOS(CHUNKINDEX(floorf(position.x / CHUNK_X_LIMIT), floorf(position.z / CHUNK_Z_LIMIT)), 
            fmodf(position.x, CHUNK_X_LIMIT), 
            position.y,
            fmodf(position.z, CHUNK_Z_LIMIT));
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


//NEED TO FIX NOW
BlockType World_getBlockAt(World *world, int x, int y, int z)
{
    if(!world || !Chunk_isValidBlockOffset(x, y, z)) return AIR;
    return world->chunk[0].blocks[x][y][z];
}