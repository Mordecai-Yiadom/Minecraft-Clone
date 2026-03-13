#ifndef MINECRAFT_CORE_GAME_WORLD_H
#define MINECRAFT_CORE_GAME_WORLD_H

#include "../../util/memtypes.h"
#include "../../util/math3D.h"

#include "chunk.h"

#define WORLD_X_LIM 128
#define WORLD_Z_LIM 128




//For now world are only one chunk
typedef struct World
{
    Chunk chunk;
    i32 loadedChunks;
    i64 seed;
}World;

World World_create(i64 seed);

#endif