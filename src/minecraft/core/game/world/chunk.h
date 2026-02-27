#ifndef MINECRAFT_CORE_GAME_WORLD_CHUNK_H
#define MINECRAFT_CORE_GAME_WORLD_CHUNK_H

#include "../../math3D.h"

#define CHUNK_LIMIT_X 16
#define CHUNK_LIMIT_Y 384
#define CHUNK_LIMIT_Z 16



typedef struct ChunkBuilder
{
    //Settings
}ChunkBuilder;

typedef struct Chunk
{   
    ivec2 position;
    int blocks[CHUNK_LIMIT_X][CHUNK_LIMIT_Y][CHUNK_LIMIT_Z];
}Chunk;

Chunk ChunkBuilder_generateChunk();

#endif