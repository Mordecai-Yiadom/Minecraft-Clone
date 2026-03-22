#ifndef MINECRAFT_CLIENT_GAME_CLIENTBLOCK_H
#define MINECRAFT_CLIENT_GAME_CLIENTBLOCK_H

#include "../../../core/core.h"

#define BLOCK_SIDE_COUNT 6

typedef struct BlockVertex
{
    vec3 position;
    vec3 normal;
    vec2 uvCoord;
    BlockType textureIndex;
}BlockVertex;

typedef struct BlockFace
{   
    BlockVertex topRight;
    BlockVertex topLeft;
    BlockVertex bottomLeft;
    BlockVertex bottomRight;
    
}BlockFace;

typedef struct BlockMesh
{
    BlockFace north;
    BlockFace south;
    BlockFace east;
    BlockFace west;
    BlockFace top;
    BlockFace bottom;
}BlockMesh;

#ifdef MINECRAFT_CLIENT_GAME_CLIENTBLOCK_C
static BlockMesh DEFAULT_BLOCKMESH;
#endif

typedef enum BlockSide
{
    BLOCKFACE_NORTH = WORLD_NORTH,
    BLOCKFACE_SOUTH = WORLD_SOUTH,
    BLOCKFACE_EAST = WORLD_EAST,
    BLOCKFACE_WEST = WORLD_WEST,
    BLOCKFACE_TOP = WORLD_UP,
    BLOCKFACE_BOTTOM = WORLD_DOWN
}BlockSide;



void BlockMesh_init();


BlockFace BlockMesh_getFace(Block block, BlockSide side);

void BlockMesh_setPosition(BlockMesh *mesh, vec3 position);

void BlockMesh_translate(BlockMesh *mesh, vec3 translation);


void BlockFace_setPosition(BlockFace *face, vec3 position);

void BlockFace_translate(BlockFace *face, vec3 translation);

#endif
