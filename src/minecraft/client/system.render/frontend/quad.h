#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_QUAD_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_QUAD_H

#include "../backend/backend.h"

#ifdef MINECRAFT_CLIENT_RENDER_SYSTEM_QUAD_C
    static Mesh QUAD_MESH;
    static float QUAD_VERTEX_DATA[] = 
    {
        1, 1, 0,    0, 0, -1,    1, 1,
        -1, 1, 0,   0, 0, -1,    0, 1,
        -1, -1, 0,  0, 0, -1,    0, 0,
        1, -1, 0,   0, 0, -1,    1, 0,    
    };

    static int QUAD_INDEX_DATA[] =
    {
        0, 1, 3,
        1, 2, 3
    };

    static inline void Quad_init();
#endif

typedef struct Quad
{
    Transform3D transform;
}Quad;


Quad Quad_create(Transform3D transform);

void Quad_draw();

void Quad_destroy(Quad *quad);


#endif