
#define MINECRAFT_CLIENT_RENDER_SYSTEM_VERTEXATTRIBUTES_C
#include "../../../core/core.h"
#include "vertexattributes.h"

//TODO Implement
VertexArray VertexArray_create()
{   
    VertexArray vao;
    glGenVertexArrays(1, (GLuint*) &vao.id);
    return vao;
}

//TODO Implement
void VertexArray_destroy(VertexArray array)
{
    glDeleteVertexArrays(1, (GLuint*) &array.id);
}

//TODO Implement
void VertexArray_bind(VertexArray array)
{
    glBindVertexArray((GLuint) array.id);
}

//TODO Implement
void VertexArray_unbind()
{
    glBindVertexArray(0);
}

bool VertexArray_isArray(VertexArray array)
{
    return (bool) glIsVertexArray((GLuint) array.id);
}

void VertexArray_addAttribute(VertexArray vertexArray, VertexBuffer refBuffer, AttributeConfiguration config)
{
    if(!VertexArray_isArray(vertexArray) || !Buffer_isBuffer(refBuffer.id)) return;

    VertexArray_bind(vertexArray);
    VertexBuffer_bind(refBuffer);

    switch(config)
    {
        case POSITION_UVCOORD_NORMAL:
            VertexArray_addAttributePOS_UV_NORM(vertexArray, refBuffer);
            break;

        case POSITION_NORMAL_UVCOORD:
        case BYTE_ARRAY:
        case INT_ARRAY:

        case VEC3f_ARRAY:
        case VEC2f_ARRAY:
        case VEC4f_ARRAY:

        case VEC2i_ARRAY:
        case VEC3i_ARRAY:
        case VEC4i_ARRAY:

        case MAT2x2_ARRAY:
        case MAT3x3_ARRAY:
            break;

        case MAT4x4_ARRAY:
            VertexArray_addAttributeMat4x4Array(vertexArray, refBuffer);
            break;
    }
}

static void VertexArray_addAttributePOS_UV_NORM(VertexArray vertexArray, VertexBuffer refBuffer)
{
    VertexArray_bind(vertexArray);
    VertexBuffer_bind(refBuffer);

    glVertexAttribPointer((GLuint) vertexArray.attributeCount, (GLint) 3, GL_FLOAT, GL_FALSE, (GLsizei) (8 * sizeof(float)), (const void*) 0);
    glVertexAttribPointer((GLuint) vertexArray.attributeCount + 1, (GLint) 2, GL_FLOAT, GL_FALSE, (GLsizei) (8 * sizeof(float)), (const void*) (3 * sizeof(float)));
    glVertexAttribPointer((GLuint) vertexArray.attributeCount + 2, (GLint) 3, GL_FLOAT, GL_FALSE, (GLsizei) (8 * sizeof(float)), (const void*) (5 * sizeof(float)));

    glEnableVertexAttribArray((GLuint) vertexArray.attributeCount);
    glEnableVertexAttribArray((GLuint) ++vertexArray.attributeCount);
    glEnableVertexAttribArray((GLuint) ++vertexArray.attributeCount);

    VertexArray_unbind();
    VertexBuffer_unbind();
}

static void VertexArray_addAttributeMat4x4Array(VertexArray vertexArray, VertexBuffer refBuffer)
{
    VertexArray_bind(vertexArray);
    VertexBuffer_bind(refBuffer);

    glVertexAttribPointer((GLuint) vertexArray.attributeCount, (GLint) 4, GL_FLOAT, GL_FALSE, (GLsizei) (4 * sizeof(float)), (const void*) 0);
    glVertexAttribPointer((GLuint) vertexArray.attributeCount + 1, (GLint) 4, GL_FLOAT, GL_FALSE, (GLsizei) (4 * sizeof(float)), (const void*) (1 * sizeof(vec4)));
    glVertexAttribPointer((GLuint) vertexArray.attributeCount + 2, (GLint) 4, GL_FLOAT, GL_FALSE, (GLsizei) (4 * sizeof(float)), (const void*) (2 * sizeof(vec4)));
    glVertexAttribPointer((GLuint) vertexArray.attributeCount + 3, (GLint) 4, GL_FLOAT, GL_FALSE, (GLsizei) (4 * sizeof(float)), (const void*) (3 * sizeof(vec4)));

    glEnableVertexAttribArray((GLuint) vertexArray.attributeCount);
    glVertexAttribDivisor((GLuint) vertexArray.attributeCount++, 1);

    glEnableVertexAttribArray((GLuint) vertexArray.attributeCount);
    glVertexAttribDivisor((GLuint) vertexArray.attributeCount++, 1);

    glEnableVertexAttribArray((GLuint) vertexArray.attributeCount);
    glVertexAttribDivisor((GLuint) vertexArray.attributeCount++, 1);

    glEnableVertexAttribArray((GLuint) vertexArray.attributeCount);
    glVertexAttribDivisor((GLuint) vertexArray.attributeCount++, 1);

    VertexArray_unbind();
    VertexBuffer_unbind();
}


