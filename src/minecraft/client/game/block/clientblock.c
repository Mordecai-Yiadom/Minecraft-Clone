#define MINECRAFT_CLIENT_GAME_CLIENTBLOCK_C
#include "clientblock.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void BlockMesh_init()
{   
    //NORTH FACE (-Z)
    BlockFace north;
    vec3f(north.topRight.position, 1, 1, -1);
    vec3f(north.topRight.normal, 0, 0, -1);
    vec2f(north.topRight.uvCoord, 1, 1);

    vec3f(north.topLeft.position, -1, 1, -1);
    vec3f(north.topLeft.normal, 0, 0, -1);
    vec2f(north.topLeft.uvCoord, 0, 1);

    vec3f(north.bottomLeft.position, -1, -1, -1);
    vec3f(north.bottomLeft.normal, 0, 0, -1);
    vec2f(north.bottomLeft.uvCoord, 0, 0);

    vec3f(north.bottomRight.position, 1, -1, -1);
    vec3f(north.bottomRight.normal, 0, 0, -1);
    vec2f(north.bottomRight.uvCoord, 1, 0);
    

    //SOUTH FACE (+Z)
    BlockFace south;
    vec3f(south.topRight.position, -1, 1, 1);
    vec3f(south.topRight.normal, 0, 0, 1);
    vec2f(south.topRight.uvCoord, 1, 1);

    vec3f(south.topLeft.position, 1, 1, 1);
    vec3f(south.topLeft.normal, 0, 0, 1);
    vec2f(south.topLeft.uvCoord, 0, 1);

    vec3f(south.bottomLeft.position, 1, -1, 1);
    vec3f(south.bottomLeft.normal, 0, 0, 1);
    vec2f(south.bottomLeft.uvCoord, 0, 0);

    vec3f(south.bottomRight.position, -1, -1, 1);
    vec3f(south.bottomRight.normal, 0, 0, 1);
    vec2f(south.bottomRight.uvCoord, 1, 0);

    //EAST FACE (+X)
    BlockFace east;
    vec3f(east.topRight.position, -1, 1, -1);
    vec3f(east.topRight.normal, 1, 0, 0);
    vec2f(east.topRight.uvCoord, 1, 1);

    vec3f(east.topLeft.position, -1, 1, 1);
    vec3f(east.topLeft.normal, 1, 0, 0);
    vec2f(east.topLeft.uvCoord, 0, 1);

    vec3f(east.bottomLeft.position, -1, -1, 1);
    vec3f(east.bottomLeft.normal, 1, 0, 0);
    vec2f(east.bottomLeft.uvCoord, 0, 0);

    vec3f(east.bottomRight.position, -1, -1, -1);
    vec3f(east.bottomRight.normal, 1, 0, 0);
    vec2f(east.bottomRight.uvCoord, 1, 0);


    //WEST FACE (-X)
    BlockFace west;
    vec3f(west.topRight.position, 1, 1, 1);
    vec3f(west.topRight.normal, -1, 0, 0);
    vec2f(west.topRight.uvCoord, 1, 1);

    vec3f(west.topLeft.position, 1, 1, -1);
    vec3f(west.topLeft.normal, -1, 0, 0);
    vec2f(west.topLeft.uvCoord, 0, 1);

    vec3f(west.bottomLeft.position, 1, -1, -1);
    vec3f(west.bottomLeft.normal, -1, 0, 0);
    vec2f(west.bottomLeft.uvCoord, 0, 0);

    vec3f(west.bottomRight.position, 1, -1, 1);
    vec3f(west.bottomRight.normal, -1, 0, 0);
    vec2f(west.bottomRight.uvCoord, 1, 0);


    //TOP FACE (+Y)
    BlockFace top;
    vec3f(top.topRight.position, -1, 1, -1);
    vec3f(top.topRight.normal, 0, 1, 0);
    vec2f(top.topRight.uvCoord, 1, 1);

    vec3f(top.topLeft.position, 1, 1, -1);
    vec3f(top.topLeft.normal, 0, 1, 0);
    vec2f(top.topLeft.uvCoord, 0, 1);

    vec3f(top.bottomLeft.position, 1, 1, 1);
    vec3f(top.bottomLeft.normal, 0, 1, 0);
    vec2f(top.bottomLeft.uvCoord, 0, 0);

    vec3f(top.bottomRight.position, -1, 1, 1);
    vec3f(top.bottomRight.normal, 0, 1, 0);
    vec2f(top.bottomRight.uvCoord, 1, 0);

    //BOTTOM FACE (-Y)
    BlockFace bottom;
    vec3f(bottom.topRight.position, -1, -1, -1);
    vec3f(bottom.topRight.normal, 0, -1, 0);
    vec2f(bottom.topRight.uvCoord, 1, 1);

    vec3f(bottom.topLeft.position, 1, -1, -1);
    vec3f(bottom.topLeft.normal, 0, -1, 0);
    vec2f(bottom.topLeft.uvCoord, 0, 1);

    vec3f(bottom.bottomLeft.position, 1, -1, 1);
    vec3f(bottom.bottomLeft.normal, 0, -1, 0);
    vec2f(bottom.bottomLeft.uvCoord, 0, 0);

    vec3f(bottom.bottomRight.position, -1, -1, 1);
    vec3f(bottom.bottomRight.normal, 0, -1, 0);
    vec2f(bottom.bottomRight.uvCoord, 1, 0);


    DEFAULT_BLOCKMESH.north = north;
    DEFAULT_BLOCKMESH.south = south;
    DEFAULT_BLOCKMESH.east = east;
    DEFAULT_BLOCKMESH.west = west;
    DEFAULT_BLOCKMESH.top = top;
    DEFAULT_BLOCKMESH.bottom = bottom;
}

BlockFace BlockMesh_getFace(BlockType type, BlockSide side)
{   
    BlockFace face;

    switch(side)
    {
        case BLOCKFACE_NORTH:
            memcpy(&face, &DEFAULT_BLOCKMESH.north, sizeof(BlockFace));
            break;

        case BLOCKFACE_SOUTH:
            memcpy(&face, &DEFAULT_BLOCKMESH.south, sizeof(BlockFace));
            break;

        case BLOCKFACE_EAST:
            memcpy(&face, &DEFAULT_BLOCKMESH.east, sizeof(BlockFace));
            break;

        case BLOCKFACE_WEST:
            memcpy(&face, &DEFAULT_BLOCKMESH.west, sizeof(BlockFace));
            break;

        case BLOCKFACE_TOP:
            memcpy(&face, &DEFAULT_BLOCKMESH.top, sizeof(BlockFace));
            break;

        case BLOCKFACE_BOTTOM:
            memcpy(&face, &DEFAULT_BLOCKMESH.bottom, sizeof(BlockFace));
            break;
    }

    face.topRight.textureID = type;
    face.topLeft.textureID = type;
    face.bottomLeft.textureID = type;
    face.bottomRight.textureID = type;
    return face;
}


void BlockMesh_setPosition(BlockMesh *mesh, vec3 position)
{
    if(!mesh) return;
    BlockFace_setPosition(&mesh->north, position);
    BlockFace_setPosition(&mesh->south, position);
    BlockFace_setPosition(&mesh->east, position);
    BlockFace_setPosition(&mesh->west, position);
    BlockFace_setPosition(&mesh->top, position);
    BlockFace_setPosition(&mesh->bottom, position);
}

void BlockMesh_translate(BlockMesh *mesh, vec3 translation)
{
    if(!mesh) return;
    BlockFace_translate(&mesh->north, translation);
    BlockFace_translate(&mesh->south, translation);
    BlockFace_translate(&mesh->east, translation);
    BlockFace_translate(&mesh->west, translation);
    BlockFace_translate(&mesh->top, translation);
    BlockFace_translate(&mesh->bottom, translation);
}


void BlockFace_setPosition(BlockFace *face, vec3 position)
{
    if(!face) return;
    glm_vec3_copy(position, face->topRight.position);
    glm_vec3_copy(position, face->topLeft.position);
    glm_vec3_copy(position, face->bottomLeft.position);
    glm_vec3_copy(position, face->bottomRight.position);
}

void BlockFace_translate(BlockFace *face, vec3 translation)
{
    if(!face) return;
    glm_vec3_add(translation, face->topRight.position, face->topRight.position);
    glm_vec3_add(translation, face->topLeft.position, face->topLeft.position);
    glm_vec3_add(translation, face->bottomLeft.position, face->bottomLeft.position);
    glm_vec3_add(translation, face->bottomRight.position, face->bottomRight.position);
}