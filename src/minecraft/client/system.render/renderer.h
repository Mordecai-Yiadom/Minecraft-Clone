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

typedef enum RendererFeature
{
    DEPTH_TEST = GL_DEPTH_TEST,
    STENCIL_TEST = GL_STENCIL_TEST,
}RendererFeature;

void Renderer_drawPoint();

void Renderer_drawLine();

void Renderer_drawQuad(Quad quad);

void Renderer_drawMesh();

void Renderer_drawBatch();

void Renderer_enableCulling();

void Renderer_clear(RendererBuffer buffer);

void Renderer_setClearColor(Color color);

void Renderer_enable(RendererFeature feature);



#endif