#ifndef MINECRAFT_CLIENT_RENDERTARGET_H
#define MINECRAFT_CLIENT_RENDERTARGET_H

#include "frontend/camera.h"

typedef struct RenderTarget
{
    Camera camera;
    //Framebuffer
}RenderTarget;

RenderTarget RenderTarget_create(Camera camera);

RenderTarget RenderTarget_destroy(RenderTarget *renderTarget);

#endif