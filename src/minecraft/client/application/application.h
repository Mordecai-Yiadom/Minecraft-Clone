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

typedef struct ClientApplication
{
    RenderSystem *renderSystem;
    Window *gameWindow;
    ArrayList appLayerStack;
    bool isRunning;
    bool isInitialized;
}ClientApplication;




bool ClientApplication_create(ApplicationInfo appInfo);

void ClientApplication_launch();

Window* ClientApplication_getGameWindow();

void ClientApplication_pushLayer(ApplicationLayer layer);

ApplicationLayer* ClientApplication_getLayer(ApplicationLayerType layerType);

void ClientApplication_terminate();


#endif