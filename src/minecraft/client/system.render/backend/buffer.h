#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_BUFFER_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_BUFFER_H

#include "bufferlayout.h"
#include "context.h"
#include "backend_types.h"
#include "shader.h"
#define BUFFER_DATA_NULL ((BufferData){.size=0, .buffer= NULL})

#define INDEXBUFFER_NULL ((IndexBuffer){.id=0})
#define UNIFORMBUFFER_NULL ((UniformBuffer){.id=0})
#define VERTEXBUFFER_NULL ((VertexBuffer){.id=0})

typedef unsigned int bufferId_t;

//TODO: Implement better usage options
enum BufferUsage
{   
    STREAM_DRAW = GL_STREAM_DRAW, 
    STREAM_READ = GL_STREAM_READ,
    STREAM_COPY = GL_STREAM_COPY, 
    STATIC_DRAW = GL_STATIC_DRAW, 
    STATIC_READ = GL_STATIC_READ, 
    STATIC_COPY = GL_STATIC_COPY, 
    DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
    DYNAMIC_READ = GL_DYNAMIC_READ, 
    DYNAMIC_COPY = GL_DYNAMIC_COPY,
};


typedef struct VertexBuffer
{   
    BufferLayout layout;
    unsigned int id;
}VertexBuffer;

typedef struct IndexBuffer
{   
    Primative type;
    unsigned int id;
}IndexBuffer;

typedef struct UniformBuffer
{   
    BufferLayout layout;
    unsigned int id;
}UniformBuffer;

#ifdef MINECRAFT_CLIENT_RENDER_SYSTEM_BUFFER_C
    static inline unsigned int Buffer_create(GLenum target, BufferData data, enum BufferUsage usage);

    static inline void Buffer_destroy(unsigned int bufferId);


    static inline void Buffer_write(GLenum target, unsigned int bufferId, BufferData data, size_t offset);

    static inline BufferData Buffer_read(GLenum target, unsigned int bufferId);

    static inline void Buffer_bind(GLenum target, unsigned int bufferId);

    static inline void Buffer_unbind(GLenum target);

    static inline int Buffer_getSize(GLenum target, unsigned int bufferId);

    static inline bool Buffer_isValid(unsigned int bufferId);
#endif

//Vertex Buffer

VertexBuffer VertexBuffer_create(BufferData data, enum BufferUsage usage, BufferLayout layout);

void VertexBuffer_destroy(VertexBuffer *buffer);

void VertexBuffer_write(VertexBuffer *buffer, BufferData data, size_t offset);

BufferData VertexBuffer_read(VertexBuffer *buffer);

void VertexBuffer_bind(VertexBuffer *buffer);

void VertexBuffer_unbind();

int VertexBuffer_getSize(VertexBuffer *buffer);

bool VertexBuffer_isValid(VertexBuffer *buffer);

int VertexBuffer_vertexCount(VertexBuffer *buffer);

//Index Buffer

IndexBuffer IndexBuffer_create(BufferData data, enum BufferUsage usage, Primative type);

void IndexBuffer_destroy(IndexBuffer *buffer);

void IndexBuffer_write(IndexBuffer *buffer, BufferData data, size_t offset);

BufferData IndexBuffer_read(IndexBuffer *buffer);

void IndexBuffer_bind(IndexBuffer *buffer);

void IndexBuffer_unbind();

int IndexBuffer_getSize(IndexBuffer *buffer);

int IndexBuffer_length(IndexBuffer *buffer);

bool IndexBuffer_isValid(IndexBuffer *buffer);


//Uniform Buffer

UniformBuffer UniformBuffer_create(BufferData data, enum BufferUsage usage, BufferLayout layout);

void UniformBuffer_destroy(UniformBuffer *buffer);

void UniformBuffer_write(UniformBuffer *buffer, BufferData data, size_t offset);

void UniformBuffer_setBindingPoint(UniformBuffer *buffer, UniformBlockBindingPoint bindingPoint);

BufferData UniformBuffer_read(UniformBuffer *buffer);

void UniformBuffer_bind(UniformBuffer *buffer);

void UniformBuffer_unbind();

int UniformBuffer_getSize(UniformBuffer *buffer);

bool UniformBuffer_isValid(UniformBuffer *buffer);

#endif