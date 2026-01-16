#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_MESH_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_MESH_H

#include "vertexattributes.h"

typedef struct Mesh
{   
    IndexBuffer ebo;
    VertexArray vao;
}Mesh;

typedef struct MeshData
{

}MeshData;


Mesh* Mesh_create();
Mesh* Mesh_destroy();
#endif