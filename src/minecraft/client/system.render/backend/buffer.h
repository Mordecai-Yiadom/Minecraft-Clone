#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_BUFFER_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_BUFFER_H

#define BUFFER_DATA_NULL ((BufferData){.size=0, .buffer= NULL})
#include "context.h"
#include <stdbool.h>
#include <string.h>

typedef unsigned int bufferId_t;

//TODO: Implement better usage options
enum BufferUsage
{   
    STREAM_DRAW = GL_STREAM_DRAW, 
    STREAM_READ,
    STREAM_COPY, 
    STATIC_DRAW, 
    STATIC_READ, 
    STATIC_COPY, 
    DYNAMIC_DRAW,
    DYNAMIC_READ, 
    DYNAMIC_COPY,
};

typedef struct BufferData
{
    size_t size;
    void* buffer;
}BufferData;

typedef struct VertexBuffer
{
    unsigned int id;
}VertexBuffer;

typedef struct IndexBuffer
{
    unsigned int id;
}IndexBuffer;

typedef struct UniformBuffer
{
    unsigned int id;
}UniformBuffer;



#ifdef MINECRAFT_CLIENT_RENDER_SYSTEM_BUFFER_C
    static inline unsigned int Buffer_create(GLenum target, BufferData data, enum BufferUsage usage);

    static inline void Buffer_destroy(unsigned int bufferId);


    static inline void Buffer_write(GLenum target, unsigned int bufferId, BufferData data, size_t offset);

    static inline BufferData Buffer_read(GLenum target, unsigned int bufferId);
    

    static inline void Buffer_bind(GLenum target, unsigned int bufferId);

    static inline void Buffer_unbind(GLenum target);
#endif

bool Buffer_isBuffer(unsigned int bufferId);

VertexBuffer VertexBuffer_create(BufferData data, enum BufferUsage usage);

void VertexBuffer_write(VertexBuffer buffer, BufferData data, size_t offset);

BufferData VertexBuffer_read(VertexBuffer buffer);

void VertexBuffer_destroy(VertexBuffer buffer);

void VertexBuffer_bind(VertexBuffer buffer);

void VertexBuffer_unbind();


IndexBuffer IndexBuffer_create(VertexBuffer bufferToIndex, BufferData data, enum BufferUsage usage);

void IndexBuffer_destroy(IndexBuffer buffer);

void IndexBuffer_write(IndexBuffer buffer, BufferData data, size_t offset);

BufferData IndexBuffer_read(IndexBuffer buffer);

void IndexBuffer_bind(IndexBuffer buffer);

void IndexBuffer_unbind();


UniformBuffer UniformBuffer_create(BufferData data, enum BufferUsage usage);

void UniformBuffer_destroy(UniformBuffer buffer);

void UniformBuffer_write(UniformBuffer buffer, BufferData data, size_t offset);

BufferData UniformBuffer_read(UniformBuffer buffer);

void UniformBuffer_bind(UniformBuffer buffer);

void UniformBuffer_unbind();



#endif