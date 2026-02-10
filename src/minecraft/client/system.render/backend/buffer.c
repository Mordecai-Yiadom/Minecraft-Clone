#define MINECRAFT_CLIENT_RENDER_SYSTEM_BUFFER_C
#include "buffer.h"


static inline unsigned int Buffer_create(GLenum target, BufferData data, enum BufferUsage usage)
{
    GLuint vbo = 0;
    glGenBuffers(1, (GLuint*) &vbo);
    Buffer_bind(target, vbo);
    glBufferData(target, (GLsizeiptr) data.size, (const void*) data.buffer, (GLenum) usage);
    Buffer_unbind(target);
    return vbo;
}

static inline void Buffer_destroy(unsigned int bufferId)
{
    glDeleteBuffers(1, (const GLuint*)(&bufferId));
}

static inline void Buffer_write(GLenum target, unsigned int bufferId, BufferData data, size_t offset)
{
    if(!Buffer_isValid(bufferId)) return;

    Buffer_bind(target, bufferId);
    glBufferSubData(target, (GLintptr) offset, (GLsizeiptr) data.size, (const void*) data.buffer);
    Buffer_unbind(target);
}

static inline BufferData Buffer_read(GLenum target, unsigned int bufferId)
{
    BufferData data;
    Buffer_bind(target, bufferId);
    data.buffer = glMapBuffer(target, GL_READ_ONLY);

    if(!data.buffer) data.size = 0;
    else glGetBufferParameteriv(target, GL_BUFFER_SIZE, (GLint*) &data.size);

    glUnmapBuffer(target);
    VertexBuffer_unbind();
    return data;
}

static inline void Buffer_bind(GLenum target, unsigned int bufferId)
{
    glBindBuffer(target, (GLuint) bufferId);
}

static inline void Buffer_unbind(GLenum target)
{
    glBindBuffer(target, 0);
}

static inline int Buffer_getSize(GLenum target, unsigned int bufferId)
{   
    Buffer_bind(target, bufferId);
    int size;
    glGetBufferParameteriv(target, GL_BUFFER_SIZE, &size);
    Buffer_unbind(target);
    return size;
}


static inline bool Buffer_isValid(unsigned int bufferId)
{
    return (bool) glIsBuffer((GLuint)bufferId);
}


VertexBuffer VertexBuffer_create(BufferData data, enum BufferUsage usage)
{   
    return (VertexBuffer){.id=Buffer_create(GL_ARRAY_BUFFER, data, usage)};
}

void VertexBuffer_destroy(VertexBuffer buffer)
{
    Buffer_destroy(buffer.id);
}

void VertexBuffer_write(VertexBuffer buffer, BufferData data, size_t offset)
{   
    Buffer_write(GL_ARRAY_BUFFER, buffer.id, data, offset);
}

BufferData VertexBuffer_read(VertexBuffer buffer)
{   
    return Buffer_read(GL_ARRAY_BUFFER, buffer.id);
}

void VertexBuffer_bind(VertexBuffer buffer)
{
    Buffer_bind(GL_ARRAY_BUFFER, buffer.id);
}

void VertexBuffer_unbind()
{
    Buffer_unbind(GL_ARRAY_BUFFER);
}

int VertexBuffer_getSize(VertexBuffer buffer)
{
    if(!Buffer_isValid(buffer.id)) return -1;
    return Buffer_getSize(GL_ARRAY_BUFFER, buffer.id);
}

bool VertexBuffer_isValid(VertexBuffer buffer)
{
    return Buffer_isValid(buffer.id);
}



IndexBuffer IndexBuffer_create(VertexArray refArray, BufferData data, enum BufferUsage usage)
{   
    if(VertexArray_isArray(refArray)) return ((IndexBuffer){.id=0});
    VertexArray_bind(refArray);
    IndexBuffer ebo = {.id=Buffer_create(GL_ELEMENT_ARRAY_BUFFER, data, usage)};
    VertexArray_unbind();
    IndexBuffer_unbind();
    return ebo;
}

void IndexBuffer_destroy(IndexBuffer buffer)
{
    Buffer_destroy(buffer.id);
}

void IndexBuffer_write(IndexBuffer buffer, BufferData data, size_t offset)
{   
    Buffer_write(GL_ELEMENT_ARRAY_BUFFER, buffer.id, data, offset);
}

BufferData IndexBuffer_read(IndexBuffer buffer)
{   
    return Buffer_read(GL_ELEMENT_ARRAY_BUFFER, buffer.id);
}

void IndexBuffer_bind(IndexBuffer buffer)
{
    Buffer_bind(GL_ELEMENT_ARRAY_BUFFER, buffer.id);
}

void IndexBuffer_unbind()
{
    Buffer_unbind(GL_ELEMENT_ARRAY_BUFFER);
}

bool IndexBuffer_isValid(IndexBuffer buffer)
{
    return Buffer_isValid(buffer.id);
}



UniformBuffer UniformBuffer_create(BufferData data, enum BufferUsage usage)
{
    return (UniformBuffer){.id=Buffer_create(GL_UNIFORM_BUFFER, data, usage)};
}

void UniformBuffer_destroy(UniformBuffer buffer)
{
    Buffer_destroy(buffer.id);
}

void UniformBuffer_write(UniformBuffer buffer, BufferData data, size_t offset)
{
    Buffer_write(GL_UNIFORM_BUFFER, buffer.id, data, offset);
}

BufferData UniformBuffer_read(UniformBuffer buffer)
{
    return Buffer_read(GL_UNIFORM_BUFFER, buffer.id);
}

void UniformBuffer_bind(UniformBuffer buffer)
{
    Buffer_bind(GL_UNIFORM_BUFFER, buffer.id);
}

void UniformBuffer_unbind()
{
    Buffer_unbind(GL_UNIFORM_BUFFER);
}

bool UniformBuffer_isValid(UniformBuffer buffer)
{
    return Buffer_isValid(buffer.id);
}
