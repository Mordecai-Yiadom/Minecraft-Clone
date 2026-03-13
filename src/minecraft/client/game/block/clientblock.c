#define MINECRAFT_CLIENT_GAME_CLIENTBLOCK_C
#include "clientblock.h"


void BlockMesh_init()
{   
    //NORTH FACE (-Z)
    BlockFace north;
    vec3f(north.topRight.position, 1, 1, -0.5);
    vec3f(north.topRight.normal, 0, 0, -1);
    vec2f(north.topRight.uvCoord, 1, 1);

    vec3f(north.topLeft.position, -1, 1, -0.5);
    vec3f(north.topLeft.normal, 0, 0, -1);
    vec2f(north.topLeft.uvCoord, 0, 1);

    vec3f(north.botttomLeft.position, -1, -1, -0.5);
    vec3f(north.botttomLeft.normal, 0, 0, -1);
    vec2f(north.botttomLeft.uvCoord, 0, 0);

    vec3f(north.bottomRight.position, 1, -1, -0.5);
    vec3f(north.bottomRight.normal, 0, 0, -1);
    vec2f(north.bottomRight.uvCoord, 1, 0);
    

    //SOUTH FACE (+Z)
    BlockFace south;
    vec3f(south.topRight.position, -1, 1, 0.5);
    vec3f(south.topRight.normal, 0, 0, 1);
    vec2f(south.topRight.uvCoord, 1, 1);

    vec3f(south.topLeft.position, 1, 1, 0.5);
    vec3f(south.topLeft.normal, 0, 0, 1);
    vec2f(south.topLeft.uvCoord, 0, 1);

    vec3f(south.botttomLeft.position, 1, -1, 0.5);
    vec3f(south.botttomLeft.normal, 0, 0, 1);
    vec2f(south.botttomLeft.uvCoord, 0, 0);

    vec3f(south.bottomRight.position, -1, -1, 0.5);
    vec3f(south.bottomRight.normal, 0, 0, 1);
    vec2f(south.bottomRight.uvCoord, 1, 0);

    //EAST FACE (+X)
    BlockFace east;
    vec3f(east.topRight.position, -1, 1, -0.5);
    vec3f(east.topRight.normal, 1, 0, 0);
    vec2f(east.topRight.uvCoord, 1, 1);

    vec3f(east.topLeft.position, -1, 1, 0.5);
    vec3f(east.topLeft.normal, 1, 0, 0);
    vec2f(east.topLeft.uvCoord, 0, 1);

    vec3f(east.botttomLeft.position, -1, -1, 0.5);
    vec3f(east.botttomLeft.normal, 1, 0, 0);
    vec2f(east.botttomLeft.uvCoord, 0, 0);

    vec3f(east.bottomRight.position, -1, -1, -0.5);
    vec3f(east.bottomRight.normal, 1, 0, 0);
    vec2f(east.bottomRight.uvCoord, 1, 0);


    //WEST FACE (-X)
    BlockFace west;
    vec3f(west.topRight.position, 1, 1, 0.5);
    vec3f(west.topRight.normal, -1, 0, 0);
    vec2f(west.topRight.uvCoord, 1, 1);

    vec3f(west.topLeft.position, 1, 1, -0.5);
    vec3f(west.topLeft.normal, -1, 0, 0);
    vec2f(west.topLeft.uvCoord, 0, 1);

    vec3f(west.botttomLeft.position, 1, -1, -0.5);
    vec3f(west.botttomLeft.normal, -1, 0, 0);
    vec2f(west.botttomLeft.uvCoord, 0, 0);

    vec3f(west.bottomRight.position, 1, -1, 0.5);
    vec3f(west.bottomRight.normal, -1, 0, 0);
    vec2f(west.bottomRight.uvCoord, 1, 0);


    //TOP FACE (+Y)
    BlockFace top;
    vec3f(top.topRight.position, -1, 1, -0.5);
    vec3f(top.topRight.normal, 0, 1, 0);
    vec2f(top.topRight.uvCoord, 1, 1);

    vec3f(top.topLeft.position, 1, 1, -0.5);
    vec3f(top.topLeft.normal, 0, 1, 0);
    vec2f(top.topLeft.uvCoord, 0, 1);

    vec3f(top.botttomLeft.position, 1, 1, 0.5);
    vec3f(top.botttomLeft.normal, 0, 1, 0);
    vec2f(top.botttomLeft.uvCoord, 0, 0);

    vec3f(top.bottomRight.position, -1, 1, 0.5);
    vec3f(top.bottomRight.normal, 0, 1, 0);
    vec2f(top.bottomRight.uvCoord, 1, 0);

    //BOTTOM FACE (-Y)
    BlockFace bottom;
    vec3f(bottom.topRight.position, -1, -1, -0.5);
    vec3f(bottom.topRight.normal, 0, -1, 0);
    vec2f(bottom.topRight.uvCoord, 1, 1);

    vec3f(bottom.topLeft.position, 1, -1, -0.5);
    vec3f(bottom.topLeft.normal, 0, -1, 0);
    vec2f(bottom.topLeft.uvCoord, 0, 1);

    vec3f(bottom.botttomLeft.position, 1, -1, 0.5);
    vec3f(bottom.botttomLeft.normal, 0, -1, 0);
    vec2f(bottom.botttomLeft.uvCoord, 0, 0);

    vec3f(bottom.bottomRight.position, -1, -1, 0.5);
    vec3f(bottom.bottomRight.normal, 0, -1, 0);
    vec2f(bottom.bottomRight.uvCoord, 1, 0);


    DEFAULT_BLOCKMESH.north = north;
    DEFAULT_BLOCKMESH.south = south;
    DEFAULT_BLOCKMESH.east = east;
    DEFAULT_BLOCKMESH.west = west;
    DEFAULT_BLOCKMESH.top = top;
    DEFAULT_BLOCKMESH.bottom = bottom;
}
