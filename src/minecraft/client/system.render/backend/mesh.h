#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_MESH_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_MESH_H

#include "../../../core/core.h"
#include "buffer.h"
#include "vertexarray.h"

typedef struct Mesh
{   
    VertexArray vao;
    IndexBuffer ebo;
    VertexBuffer vbo;
}Mesh;

typedef struct MeshTransform
{
    vec3 position;
    vec3 scale;
    vec3 rotation;
}MeshTransform;

Mesh* Mesh_create();
Mesh* Mesh_destroy();
#endif