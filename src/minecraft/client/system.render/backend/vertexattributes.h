#include "buffer.h"

typedef struct VertexArray
{
    unsigned int id;
}VertexArray;

typedef enum AttribDataType
{
    BYTE = GL_BYTE,
    UNSIGNED_BYTE,
    SHORT,
    UNSIGNED_SHORT,
    INT,
    UNSIGNED_INT,
    FLOAT
}AttribDataType;

typedef enum VertexArrayDataPattern
{
    INTERLEAVED,
    CONTIGUOUS,
}VertexArrayDataPattern;

typedef struct VertexArrayLayout
{
    unsigned int attribPointerCount;
    AttribDataType dataType;

}VertexArrayLayout;




VertexArray VertexArray_create(VertexBuffer buffer);

void VertexArray_destroy(VertexArray array);

void VertexArray_bind(VertexArray array);

void VertexArray_unbind();