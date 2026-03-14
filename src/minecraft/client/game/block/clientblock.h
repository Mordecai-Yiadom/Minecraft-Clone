#ifndef MINECRAFT_CLIENT_GAME_CLIENTBLOCK_H
#define MINECRAFT_CLIENT_GAME_CLIENTBLOCK_H

#include "../../../core/core.h"
#include "../../system.render/renderers/chunkrenderer.h"


typedef struct BlockVertex
{
    vec3 position;
    vec3 normal;
    vec2 uvCoord;
    u32 textureID;
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
    BLOCKFACE_NORTH,
    BLOCKFACE_SOUTH,
    BLOCKFACE_EAST,
    BLOCKFACE_WEST,
    BLOCKFACE_TOP,
    BLOCKFACE_BOTTOM
}BlockSide;


void BlockMesh_init();


BlockFace BlockMesh_getFace(BlockType type, BlockSide side);



#endif
