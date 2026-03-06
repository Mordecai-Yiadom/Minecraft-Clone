#ifndef MINECRAFT_CLIENT_RENDERER_H
#define MINECRAFT_CLIENT_RENDERER_H

#include "backend/backend.h"
#include "frontend/frontend.h"
#include "../../core/color.h"

typedef enum RendererBuffer
{
    COLOR_BUFFER = GL_COLOR_BUFFER_BIT,
    DEPTH_BUFFER = GL_DEPTH_BUFFER_BIT,
    STENCIL_BUFFER = GL_STENCIL_BUFFER_BIT,
}RendererBuffer;

typedef enum RendererTest
{
    DEPTH_TEST = GL_DEPTH_TEST,
    STENCIL_TEST = GL_STENCIL_TEST,
}RendererTest;

typedef enum RendererCullMode
{
    FRONT = GL_FRONT,
    BACK = GL_BACK,
    FRONT_AND_BACK = GL_FRONT_AND_BACK,
}RendererCullMode;


typedef enum RendererPolygonMode
{
    POINT = GL_POINT,
    LINE = GL_LINE,
    FILL = GL_FILL,
}RendererPolygonMode;


void Renderer_drawPoint();

void Renderer_drawLine();

void Renderer_drawMesh(Mesh *mesh);

void Renderer_drawMeshInstanced(Mesh *mesh);

void Renderer_setPolygonMode(RendererPolygonMode mode);

void Renderer_clearBuffer(RendererBuffer buffer);

void Renderer_setClearColor(Color color);

void Renderer_enableTest(RendererTest test);

void Renderer_disableTest(RendererTest test);

void Renderer_setCullMode(RendererCullMode cullMode);

void Renderer_enableCulling();

void Renderer_disableCulling();

void Renderer_setViewport(int xOrigin, int yOrigin, int width, int height);




#endif