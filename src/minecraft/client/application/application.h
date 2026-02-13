#ifndef MINECRAFT_CLIENT_APPLICATION_H
#define MINECRAFT_CLIENT_APPLICATION_H

#include "layers/layer.h"
#include "../system.render/rendersystem.h"


typedef struct ApplicationInfo
{   
    WindowProps props;
    char **argv;
    int argc;
}ApplicationInfo;

typedef struct MinecraftClientApplication
{
    RenderSystem *renderSystem;
    Window *gameWindow;
    bool isRunning;
    ApplicationLayer layerStack[];
}MinecraftClientApplication;




bool MinecraftClientApplication_create(ApplicationInfo *appInfo);

void MinecraftClientApplication_launch();

void MinecraftClientApplication_terminate();


#endif