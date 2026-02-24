#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_MESH_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_MESH_H

#include "../../../core/core.h"
#include "buffer.h"
#include "vertexarray.h"

typedef struct Mesh2DTransform
{
    vec2 postion;
    vec2 scale;
    vec2 rotation;
}Mesh2DTransform;

typedef struct Mesh3DTransform
{
    vec3 position;
    vec3 scale;
    vec3 rotation;
}Mesh3DTransform;

typedef struct Mesh2D
{
    VertexArray vao;
    Mesh2DTransform transform;
}Mesh2D;


typedef struct Mesh3D
{   
    VertexArray vao;
    Mesh3DTransform transform;
}Mesh3D;


Mesh3D Mesh3D_create(VertexArray vao);

void Mesh3D_destroy(Mesh3D *mesh);

Mesh2D Mesh2D_create(VertexArray vao);
void Mesh2D_destroy(Mesh2D *mesh);

#endif