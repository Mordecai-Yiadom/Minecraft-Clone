#define MINECRAFT_CLIENT_RENDER_SYSTEM_BUFFER_C
#include "buffer.h"


static inline unsigned int Buffer_create(GLenum target, BufferData data, enum BufferUsage usage)
{
    GLuint vbo = 0;
    glGenBuffers(1, (GLuint*) &vbo);
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
    if(!Buffer_isBuffer(bufferId)) return;

    Buffer_bind(target, bufferId);

    size_t vboSize;
    glGetBufferParameteriv(target, GL_BUFFER_SIZE, (GLint*) &vboSize);

    if(vboSize > data.size)
    {
        void* vboBuffer = glMapBuffer(target, GL_WRITE_ONLY);
        if(!vboBuffer) return;
        
        memcpy((((size_t)vboBuffer) + (size_t)offset), (const void*) data.buffer, data.size);
        
        glUnmapBuffer(target);
    }
    else glBufferSubData(target, (GLintptr) offset, (GLsizeiptr) data.size, (const void*) data.buffer);
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

bool Buffer_isBuffer(unsigned int bufferId)
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

//POTENTIAL DATA SAFTEY ISSUE, when writing to end of buffer with a given offset
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

IndexBuffer IndexBuffer_create(VertexBuffer bufferToIndex, BufferData data, enum BufferUsage usage)
{
    VertexBuffer_bind(bufferToIndex);
    IndexBuffer ebo = {.id=Buffer_create(GL_ELEMENT_ARRAY_BUFFER, data, usage)};
    VertexBuffer_unbind();
    IndexBuffer_unbind();
    return ebo;
}

void IndexBuffer_destroy(IndexBuffer buffer)
{
    Buffer_destroy(buffer.id);
}

//POTENTIAL DATA SAFTEY ISSUE, when writing to end of buffer with a given offset
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

//TODO Implement
VertexArray VertexArray_create(VertexBuffer buffer)
{
    return (VertexArray){.id=0};
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

