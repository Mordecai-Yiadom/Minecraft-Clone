#include "world.h"

#include <stdlib.h>
#include <string.h>

World World_create(i64 seed)
{
    World world;
    world.seed = seed;

    world.chunk = Chunk_create();
    return world;
}