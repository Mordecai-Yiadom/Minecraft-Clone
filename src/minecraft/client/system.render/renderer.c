#include "renderer.h"
#include "renderpass.h"
#include "rendersystem.h"
#include "commands/drawcommand.h"

void Renderer_drawMesh(Mesh *mesh)
{
    if(!Mesh_isValid(mesh)) return;
    
    RenderCommand command;
    memset(&command, 0, sizeof(RenderCommand));
    command.address = DrawMeshIndexedCommand;
    command.args = mesh;
    RenderPass_submitCommand(RenderSystem_getRenderPass(0), command);
    
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

void Renderer_setViewport(RendererViewport viewport)
{
    glViewport(viewport.xOrigin, viewport.yOrigin, viewport.width, viewport.height);
}


void Renderer_enableMSAA()
{
    glEnable(GL_MULTISAMPLE);
}

void Renderer_disableMSAA()
{
    glDisable(GL_MULTISAMPLE);
}

