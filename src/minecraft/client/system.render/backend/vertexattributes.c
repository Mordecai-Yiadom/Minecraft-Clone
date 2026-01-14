#include "vertexattributes.h"

//TODO Implement
VertexArray VertexArray_create(VertexBuffer buffer)
{   
    if(!Buffer_isBuffer(buffer.id)) return (VertexArray){.id=0};

    VertexArray vao;
    VertexBuffer_bind(buffer);
    glGenVertexArrays(1, (GLuint) &vao.id);
    glBindVertexArray((GLuint) &vao.id);
    glVertexAttribPointer();
}

//TODO Implement
void VertexArray_destroy(VertexArray array)
{}

//TODO Implement
void VertexArray_bind(VertexArray array)
{}

//TODO Implement
void VertexArray_unbind()
{}