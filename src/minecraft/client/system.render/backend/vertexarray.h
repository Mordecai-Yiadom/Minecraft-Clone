#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_VERTEXATTRIBUTES_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_VERTEXATTRIBUTES_H

#include "../../../core/core.h"
#include "backend_types.h"

typedef struct VertexArray
{
    unsigned int id;
    unsigned int attributeCount;
}VertexArray;


VertexArray VertexArray_create();

void VertexArray_destroy(VertexArray vertexArray);

void VertexArray_bind(VertexArray vertexArray);

void VertexArray_unbind();

bool VertexArray_isValid(VertexArray vertexArray);

void VertexArray_addVertexBuffer(VertexArray *vertexArray, VertexBuffer vertexBuffer);

void VertexArray_setIndexBuffer(VertexArray *vertexArray, IndexBuffer indexBuffer);

void VertexArray_enableAttribute(VertexArray vertexArray, int attributeIndex);

void VertexArray_disableAttribute(VertexArray vertexArray, int attributeIndex); 



#endif