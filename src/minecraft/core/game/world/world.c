#define MINECRAFT_CORE_GAME_WORLD_C
#include "world.h"

#include <stdlib.h>
#include <string.h>


World* World_create(i64 seed)
{
    World *world = calloc(1, sizeof(World));
    world->seed = seed;

    world->loadedChunks = ArrayList_create(25, sizeof(Chunk*), DYNAMIC_MEMORY);
    return world;
}


void World_loadChunk(World *world, ChunkIndex chunkIndex)
{
    if(!world || World_isChunkLoaded(world, chunkIndex)) 
        return;

    Chunk *chunk = Chunk_create(world, chunkIndex);
    if(chunk) ArrayList_add(&world->loadedChunks, (byte*)&chunk);
    
}

void World_loadChunkAt(World *world, WorldPosition position)
{   
    World_loadChunk(world, World_getChunkIndexAt(world, position));
}


bool World_isChunkLoaded(World *world, ChunkIndex chunkIndex)
{
    if(!world) return false;

    int loadedChunkCount = ArrayList_length(&world->loadedChunks);
    Chunk *currChunk;
    for(int i = 0; i < loadedChunkCount; i++)
    {   
        currChunk = NULL;
        ArrayList_get(&world->loadedChunks, i ,(byte*)&currChunk);

        if(!currChunk) continue;

        if(currChunk->index.xOffset == chunkIndex.xOffset 
            && currChunk->index.zOffset == chunkIndex.zOffset)
            return true;
    }

    return false;
}


Chunk* World_getChunk(World *world, ChunkIndex chunkIndex)
{
    if(!world) return NULL;
    int loadedChunkCount = ArrayList_length(&world->loadedChunks);

    Chunk *currChunk;
    for(int i = 0; i < loadedChunkCount; i++)
    {   
        currChunk = NULL;
        ArrayList_get(&world->loadedChunks, i ,(byte*)&currChunk);
        if(!currChunk) continue;

        if(currChunk->index.xOffset == chunkIndex.xOffset 
            && currChunk->index.zOffset == chunkIndex.zOffset)
            return currChunk;
    }    
    return NULL;
}

Chunk* World_getChunkAt(World *world, WorldPosition position)
{   
    return World_getChunk(world, WorldPosition_toChunkPosition(position).chunkIndex);
}


Chunk* World_getChunkAtBlock(World *world, WorldBlockPosition position)
{
    return World_getChunk(world, 
        WorldPosition_toChunkPosition(WORLDPOS(position.x, position.y, position.z)).chunkIndex);
}

ChunkIndex World_getChunkIndexAt(World *world, WorldPosition position)
{
    if(!world) return CHUNKINDEX_NULL;
    return WorldPosition_toChunkPosition(position).chunkIndex;
}

WorldPosition ChunkPosition_toWorldPosition(ChunkPosition position)
{
    return WORLDPOS(position.x + (position.chunkIndex.xOffset * CHUNK_X_LIMIT), 
        position.y, 
        position.z + (position.chunkIndex.zOffset * CHUNK_Z_LIMIT));
}

WorldBlockPosition ChunkBlockPosition_toWorldBlockPosition(ChunkBlockPosition position)
{
    return WORLDBLOCKPOS(position.x + (position.chunkIndex.xOffset * CHUNK_X_LIMIT), 
        position.y, 
        position.z + (position.chunkIndex.zOffset * CHUNK_Z_LIMIT));
}


ChunkPosition WorldPosition_toChunkPosition(WorldPosition position)
{   
    return CHUNKPOS(CHUNKINDEX((int)floorf(position.x / CHUNK_X_LIMIT), (int)floorf(position.z / CHUNK_Z_LIMIT)), 
        fmodf(position.x, CHUNK_X_LIMIT), 
        position.y,
        fmodf(position.z, CHUNK_Z_LIMIT));
}

WorldBlockPosition WorldPosition_toBlockPosition(WorldPosition position)
{
    return WORLDBLOCKPOS((int)position.x, (int)position.y, (int)position.z);
}

WorldPosition WorldPosition_floor(WorldPosition position)
{
    return WORLDPOS(floorf(position.x), floorf(position.y), floorf(position.z));
}

WorldPosition WorldPosition_ceiling(WorldPosition position)
{
    return WORLDPOS(ceilf(position.x), ceilf(position.y), ceilf(position.z));
}


void World_setBlockAt(World *world, WorldPosition position, Block block)
{
    if(!world) return;
    Chunk_setBlockAt(World_getChunkAt(world, position), WorldPosition_toChunkPosition(position), block);
}

Block World_getBlockAt(World *world, WorldPosition position)
{   
    if(!world) return BLOCK_NULL;

    ChunkPosition chunkPos = WorldPosition_toChunkPosition(position);
    Chunk* chunk = World_getChunkAt(world, position);
    return Chunk_getBlockAt(chunk, chunkPos);
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

