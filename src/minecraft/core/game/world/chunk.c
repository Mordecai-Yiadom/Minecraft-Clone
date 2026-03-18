#include "chunk.h"

#include <string.h>
#include "../block/block.h"
#include <stdlib.h>

Chunk* Chunk_create()
{
    Chunk *chunk = calloc(1, sizeof(Chunk));
    chunk->xOffset = 0;
    chunk->yOffset = 0;
    
    memset(chunk->blocks, GRASS, sizeof(chunk->blocks));

    return chunk;
}