#ifndef MINECRAFT_CLIENT_WINDOWEVENT_H
#define MINECRAFT_CLIENT_WINDOWEVENT_H

#include "../../system.render/frontend/window.h"

typedef struct WindowFrameBufferResizeEvent
{
    Window window;
    int width;
    int height;
}WindowFrameBufferResizeEvent;

typedef struct WindowCloseEvent
{
    
}WindowCloseEvent;

#endif