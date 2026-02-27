#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_MESH_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_MESH_H

#include "../../../core/core.h"

#include "backend.h"

typedef enum MeshGeometryType
{
    STATIC = STATIC_DRAW,
    DYNAMIC = DYNAMIC_DRAW
}MeshGeometryType;


typedef enum MeshFormat
{
    POS3f_NORM3f_UV2f,
    POS2f_UV2f,
    
}MeshFormat;


typedef struct MeshData
{
    BufferData vertexData;
    BufferData indexData;
    MeshFormat format;
    MeshGeometryType type;
}MeshData;

typedef struct Mesh
{   
    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ebo;
}Mesh;


Mesh Mesh_create(MeshData meshData);

void Mesh_destroy(Mesh *mesh);

bool Mesh_isValid(Mesh *mesh);

#endif