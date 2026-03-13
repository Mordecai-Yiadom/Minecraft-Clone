#ifndef MINECRAFT_CLIENT_GAME_CLIENTBLOCK_H
#define MINECRAFT_CLIENT_GAME_CLIENTBLOCK_H

#include "../../../core/core.h"
#include "../../system.render/renderers/chunkrenderer.h"



typedef struct BlockVertex
{
    vec3 position;
    vec3 normal;
    vec2 uvCoord;
}BlockVertex;

typedef struct BlockFace
{   
    BlockVertex topRight;
    BlockVertex topLeft;
    BlockVertex botttomLeft;
    BlockVertex bottomRight;
    u32 textureID;
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


void BlockMesh_init();


#endif
