#include "mesh.h"

Mesh Mesh_create(MeshData meshData)
{
    Mesh mesh; 
    BufferLayout vboLayout;
    switch(meshData.format)
    {
        case POS3f_NORM3f_UV2f:
            vboLayout = BufferLayout_create(INTERLEAVED, 3, aVEC3(FLOAT), aVEC3(FLOAT), aVEC2(FLOAT));
            break;

        case POS2f_UV2f:
            break;
    }

    mesh.vbo = VertexBuffer_create(meshData.vertexData, (enum BufferUsage) meshData.type, vboLayout);
    mesh.ebo = IndexBuffer_create(meshData.indexData, (enum BufferUsage) meshData.type, UNSIGNED_INT);
    mesh.vao = VertexArray_create(mesh.ebo, 1, mesh.vbo);
    return mesh;
}

void Mesh_destroy(Mesh *mesh)
{
    if(!mesh) return;
    VertexBuffer_destroy(&mesh->vbo);
    IndexBuffer_destroy(&mesh->ebo);
    VertexArray_destroy(&mesh->vao);
}

bool Mesh_isValid(Mesh *mesh)
{
    if(!mesh) return false;
    return VertexArray_isValid(&mesh->vao) 
    && VertexBuffer_isValid(&mesh->vbo) 
    && IndexBuffer_isValid(&mesh->ebo);
}

