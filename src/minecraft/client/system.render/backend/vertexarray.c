
#define MINECRAFT_CLIENT_RENDER_SYSTEM_VERTEXATTRIBUTES_C
#include "vertexarray.h"
#include "context.h"
#include "buffer.h"

//TODO Implement
VertexArray VertexArray_create()
{   
    VertexArray vao;
    vao.attributeCount = 0;
    glGenVertexArrays(1, (GLuint*) &vao.id);
    VertexArray_bind(vao);
    VertexArray_unbind();
    return vao;
}

//TODO Implement
void VertexArray_destroy(VertexArray vertexArray)
{
    glDeleteVertexArrays(1, (GLuint*) &vertexArray.id);
}

//TODO Implement
void VertexArray_bind(VertexArray vertexArray)
{
    glBindVertexArray((GLuint) vertexArray.id);
}

//TODO Implement
void VertexArray_unbind()
{
    glBindVertexArray(0);
}

bool VertexArray_isValid(VertexArray vertexArray)
{
    return (bool) glIsVertexArray((GLuint) vertexArray.id);
}


void VertexArray_addVertexBuffer(VertexArray *vertexArray, VertexBuffer vertexBuffer)
{   
    if(!vertexArray) return;
    if(!VertexArray_isValid(*vertexArray) || !VertexBuffer_isValid(vertexBuffer)) return;
    
    VertexArray_bind(*vertexArray);
    VertexBuffer_bind(vertexBuffer);

    for(int i = 0; i < vertexBuffer.layout.attributeCount; i++)
    {   
        if(vertexArray->attributeCount == BUFFERLAYOUT_MAX_ATTRIBUTES) break;
        glVertexAttribPointer(vertexArray->attributeCount, 
            vertexBuffer.layout.attributes[i].componentCount, 
            vertexBuffer.layout.attributes[i].componentType, 
            vertexBuffer.layout.attributes[i].isNormalized, 
            (GLsizei) vertexBuffer.layout.stride, 
            (const void*) vertexBuffer.layout.attributes[i].offset);
            
        glVertexAttribDivisor((GLuint)vertexArray->attributeCount, (GLuint) vertexBuffer.layout.attributes[i].attributeDivisor);
        glEnableVertexAttribArray((GLuint) vertexArray->attributeCount);
        ++vertexArray->attributeCount;
    }
    
    VertexArray_unbind();
    VertexBuffer_unbind();
}

void VertexArray_setIndexBuffer(VertexArray *vertexArray, IndexBuffer indexBuffer)
{
    if(!vertexArray) return;
    if(!VertexArray_isValid(*vertexArray) || !IndexBuffer_isValid(indexBuffer)) return;

    VertexArray_bind(*vertexArray);
    IndexBuffer_bind(indexBuffer);
    
    VertexArray_unbind(*vertexArray);
    IndexBuffer_unbind();
}

void VertexArray_enableAttribute(VertexArray vertexArray, int attributeIndex)
{
    if(!VertexArray_isValid(vertexArray) 
    || attributeIndex < 0 
    || attributeIndex > BUFFERLAYOUT_MAX_ATTRIBUTES - 1) return;

    VertexArray_bind(vertexArray);
    glEnableVertexAttribArray((GLuint) attributeIndex);
    VertexArray_unbind();
}

void VertexArray_disableAttribute(VertexArray vertexArray, int attributeIndex)
{
    if(!VertexArray_isValid(vertexArray) 
    || attributeIndex < 0 
    || attributeIndex > BUFFERLAYOUT_MAX_ATTRIBUTES - 1) return;

    VertexArray_bind(vertexArray);
    glDisableVertexAttribArray((GLuint) attributeIndex);
    VertexArray_unbind();
}


