#define MINECRAFT_CLIENT_RENDER_SYSTEM_QUAD_C
#include "quad.h"


static inline void Quad_init()
{   
    BufferData vertexData = {.buffer=QUAD_VERTEX_DATA, .size=sizeof(QUAD_VERTEX_DATA)};
    BufferData indexData = {.buffer=QUAD_INDEX_DATA, .size=sizeof(QUAD_INDEX_DATA)};

    MeshData meshData;
    meshData.format = POS3f_NORM3f_UV2f;
    meshData.vertexData = vertexData;
    meshData.indexData = indexData;
    meshData.type = STATIC;

    QUAD_MESH = Mesh_create(meshData);
}


Quad Quad_create(Transform3D transform)
{
    if(!Mesh_isValid(&QUAD_MESH)) Quad_init();

    Quad quad = {.transform=transform};
    return quad;
}

void Quad_draw()
{   
    int length = IndexBuffer_length(&QUAD_MESH.ebo);

    VertexArray_bind(&QUAD_MESH.vao);
    glDrawElements(GL_TRIANGLES, length, QUAD_MESH.ebo.type, NULL);
    VertexArray_unbind();
}