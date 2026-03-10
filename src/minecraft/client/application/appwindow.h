#ifndef MINECRAFT_CLIENT_APPWINDOW_H
#define MINECRAFT_CLIENT_APPWINDOW_H

#include "../system.render/frontend/window.h"
#include "../system.input/inputsystem.h"

typedef struct AppWindow
{
    Window window;
    InputContext inputContext;
}AppWindow;


#endif