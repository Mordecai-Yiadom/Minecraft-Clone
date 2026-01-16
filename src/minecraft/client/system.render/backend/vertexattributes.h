#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_VERTEXATTRIBUTES_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_VERTEXATTRIBUTES_H
#include "buffer.h"

typedef struct VertexArray
{
    unsigned int id;
    unsigned int attributeCount;
}VertexArray;

typedef enum AttribDataPattern
{
    INTERLEAVED,
    PACKED,
}AttribDataPattern;

typedef enum AttributeConfiguration
{
    POSITION_UVCOORD_NORMAL,
    POSITION_NORMAL_UVCOORD,

    BYTE_ARRAY,
    INT_ARRAY,

    VEC3f_ARRAY,
    VEC2f_ARRAY,
    VEC4f_ARRAY,

    VEC2i_ARRAY,
    VEC3i_ARRAY,
    VEC4i_ARRAY,

    MAT2x2_ARRAY,
    MAT3x3_ARRAY,
    MAT4x4_ARRAY, 
}AttributeConfiguration;


VertexArray VertexArray_create();

void VertexArray_destroy(VertexArray array);

void VertexArray_bind(VertexArray array);

void VertexArray_unbind();

bool VertexArray_isArray(VertexArray array);

//TODO: REFACTOR....PLEEEEAAAAASSSSEEEEE
void VertexArray_addAttribute(VertexArray vertexArray, VertexBuffer refBuffer, AttributeConfiguration config);

#ifdef MINECRAFT_CLIENT_RENDER_SYSTEM_VERTEXATTRIBUTES_C
    //TODO: REFACTOR....PLEEEEAAAAASSSSEEEEE
    static void VertexArray_addAttributePOS_UV_NORM(VertexArray vertexArray, VertexBuffer refBuffer);

    //TODO: REFACTOR....PLEEEEAAAAASSSSEEEEE
    static void VertexArray_addAttributeMat4x4Array(VertexArray vertexArray, VertexBuffer refBuffer);
#endif

#endif