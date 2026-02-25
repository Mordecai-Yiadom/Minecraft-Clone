#define MINECRAFT_CLIENT_RENDER_SYSTEM_QUAD_C
#include "quad.h"

static VertexArray QUAD_VAO;
static VertexBuffer QUAD_VBO;
static IndexBuffer QUAD_EBO;

static inline void Quad_init()
{   
    BufferData bufferData = {.buffer=QUAD_VERTEX_DATA, .size=sizeof(QUAD_VERTEX_DATA)};
    BufferLayout bufferLayout = BufferLayout_create(INTERLEAVED, 3, aVEC3(FLOAT), aVEC3(FLOAT), aVEC2(FLOAT));

    BufferData indexBufferData = {.buffer=QUAD_INDEX_DATA, .size=sizeof(QUAD_INDEX_DATA)};
    
    QUAD_EBO = IndexBuffer_create(indexBufferData, STATIC_DRAW, UNSIGNED_INT);
    QUAD_VBO = VertexBuffer_create(bufferData, STATIC_DRAW, bufferLayout);
    QUAD_VAO = VertexArray_create(QUAD_EBO, 1, QUAD_VBO);
}


Quad Quad_create(Transform3D transform)
{
    if(!VertexArray_isValid(&QUAD_VAO)) Quad_init();

    Quad quad = {.transform=transform};
    return quad;
}

void Quad_draw()
{   
    int length = IndexBuffer_length(&QUAD_EBO);

    VertexArray_bind(&QUAD_VAO);
    glDrawElements(GL_TRIANGLES, length, QUAD_EBO.type, NULL);
    VertexArray_unbind();
}