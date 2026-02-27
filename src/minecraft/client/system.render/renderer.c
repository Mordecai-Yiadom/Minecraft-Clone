#include "renderer.h"


void Renderer_drawMesh(Mesh *mesh)
{
    if(!Mesh_isValid(mesh)) return;
    VertexArray_bind(&mesh->vao);
    glDrawElements(GL_TRIANGLES, IndexBuffer_length(&mesh->ebo), mesh->ebo.type, NULL);
    VertexArray_unbind();
}

void Renderer_setPolygonMode(RendererPolygonMode mode)
{
    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void Renderer_clearBuffer(RendererBuffer buffer)
{
    glClear(buffer);
}

void Renderer_setClearColor(Color color)
{
    glClearColor(color.red, color.green, color.blue, color.alpha);
}

void Renderer_enableTest(RendererTest test)
{
    glEnable(test);
}

void Renderer_disableTest(RendererTest test)
{
    glDisable(test);
}

void Renderer_setCullMode(RendererCullMode cullMode)
{
    glCullFace(cullMode);
}

void Renderer_enableCulling()
{
    glEnable(GL_CULL_FACE);
}

void Renderer_disableCulling()
{
    glDisable(GL_CULL_FACE);
}

void Renderer_setViewport(int xOrigin, int yOrigin, int width, int height)
{
    glViewport(xOrigin, yOrigin, width, height);
}