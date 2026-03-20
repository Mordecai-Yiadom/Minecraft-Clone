#ifndef MINECRAFT_CORE_GAME_WORLD_H
#define MINECRAFT_CORE_GAME_WORLD_H

#include "../../util/memtypes.h"
#include "../../util/math3D.h"


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

typedef struct BlockPosition
{
    int x;
    int y;
    int z;
}BlockPosition;

//For now world are only one chunk
typedef struct World
{
    Chunk *chunk;
    i32 loadedChunks;
    i64 seed;
}World;

#ifdef MINECRAFT_CORE_GAME_WORLD_C
vec3 WORLD_NORTH_VECTOR = {0, 0, -1};
vec3 WORLD_SOUTH_VECTOR = {0, 0, 1};
vec3 WORLD_EAST_VECTOR = {1, 0, 0};
vec3 WORLD_WEST_VECTOR = {-1, 0, 0};
vec3 WORLD_UP_VECTOR = {0, 1, 0};
vec3 WORLD_DOWN_VECTOR = {0, -1, 0};
#endif

World* World_create(i64 seed);

float* World_getDirectionVector(WorldDirection direction);

BlockType World_getBlockAt(World *world, int x, int y, int z);

BlockPosition World_getBlockPosition(Chunk *chunk, int xOffset, int yOffset, int zOffset);

#endif