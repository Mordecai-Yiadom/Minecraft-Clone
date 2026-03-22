#ifndef MINECRAFT_CORE_GAME_WORLD_H
#define MINECRAFT_CORE_GAME_WORLD_H

#include "../../util/memtypes.h"
#include "../../util/math3D.h"
#include "../../util/arraylist.h"

#include "chunk.h"

#define WORLD_X_LIM 128
#define WORLD_Z_LIM 128

typedef enum WorldDirection
{
    WORLD_NORTH,
    WORLD_SOUTH,
    WORLD_EAST,
    WORLD_WEST,
    WORLD_UP,
    WORLD_DOWN,
}WorldDirection;

#ifdef MINECRAFT_CORE_GAME_WORLD_C
    static vec3 WORLD_NORTH_VECTOR = {0, 0, -1};
    static vec3 WORLD_SOUTH_VECTOR = {0, 0, 1};
    static vec3 WORLD_EAST_VECTOR = {1, 0, 0};
    static vec3 WORLD_WEST_VECTOR = {-1, 0, 0};
    static vec3 WORLD_UP_VECTOR = {0, 1, 0};
    static vec3 WORLD_DOWN_VECTOR = {0, -1, 0};
#endif

typedef struct WorldPosition
{
    float x;
    float y;
    float z;
}WorldPosition;

typedef struct WorldBlockPosition
{   
    int x;
    int y;
    int z;
}WorldBlockPosition;

//For now world are only one chunk
typedef struct World
{   
    ArrayList loadedChunks;
    i64 seed;
}World;

//Convienience macro for quickly making a WorldPosition struct
#define WORLDPOS(xp, yp, zp) ((WorldPosition){.x=(xp), .y=(yp), .z=(zp)})

//Convienience macro for quickly making a WorldBlockPosition struct
#define WORLDBLOCKPOS(xp, yp, zp) ((WorldBlockPosition){.x=(xp), .y=(yp), .z=(zp)})

World* World_create(i64 seed);

void World_destroy(World *world);

void World_loadChunk(World *world, ChunkIndex chunkIndex);

void World_loadChunkAt(World *world, WorldPosition position);

void World_unloadChunk(World *world, ChunkIndex chunkIndex);

void World_unloadChunkAt(World *world, WorldPosition position);

bool World_isChunkLoaded(World *world, ChunkIndex chunkIndex);


//Returns a loaded chunk on a given world. Returns NULL if chunk is not loaded
Chunk* World_getChunk(World *world, ChunkIndex chunkIndex);

Chunk* World_getChunkAt(World *world, WorldPosition position);


Chunk* World_getChunkAtBlock(World *world, WorldBlockPosition position);


ChunkIndex World_getChunkIndexAt(World *world, WorldPosition position);

ChunkIndex World_getChunkIndexAtBlock(World *world, WorldBlockPosition position);


WorldPosition ChunkPosition_toWorldPosition(ChunkPosition position);

WorldBlockPosition ChunkBlockPosition_toWorldBlockPosition(ChunkBlockPosition position);

ChunkPosition WorldPosition_toChunkPosition(WorldPosition position);

WorldBlockPosition WorldPosition_toBlockPosition(WorldPosition position);

WorldPosition WorldPosition_floor(WorldPosition position);

WorldPosition WorldPosition_ceiling(WorldPosition position);


void World_setBlockAt(World *world, WorldPosition position, Block block);

Block World_getBlockAt(World *world, WorldPosition position);

float* World_getDirectionVector(WorldDirection direction);

#endif