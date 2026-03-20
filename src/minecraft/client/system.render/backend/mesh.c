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

        case POS3f_NORM3f_UV2f_TEXID1i:
            vboLayout = BufferLayout_create(INTERLEAVED, 4, aVEC3(FLOAT), aVEC3(FLOAT), aVEC2(FLOAT), aVEC1(INT));
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

    bool vaoValid = VertexArray_isValid(&mesh->vao);
    bool vboValid = VertexBuffer_isValid(&mesh->vbo);
    bool eboValid = IndexBuffer_isValid(&mesh->ebo);

    // if(vaoValid) puts("VAO is valid");
    // else puts("VAO invalid");
    // printf("VAO handle: %d\n", mesh->vao.id);

    // if(vboValid) puts("VBO is valid");
    // else puts("VBO invalid");
    // printf("VBO handle: %d\n", mesh->vbo.id);

    // if(eboValid) puts("EBO is valid");
    // else puts("EBO invalid");
    // printf("EBO handle: %d\n", mesh->ebo.id);

    return (vaoValid && vboValid &&  eboValid);
}
