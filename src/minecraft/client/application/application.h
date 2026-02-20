#ifndef MINECRAFT_CLIENT_APPLICATION_H
#define MINECRAFT_CLIENT_APPLICATION_H

#include "layers/layer.h"
#include "../system.render/rendersystem.h"

typedef struct ApplicationVersion
{    
    int major;
    int minor;
}ApplicationVersion;

typedef struct ApplicationInfo
{   
    WindowProps windowProps;
    ApplicationVersion version;
    char **argv;
    int argc;
}ApplicationInfo;

typedef struct ClientApplication
{   
    ApplicationInfo appInfo;
    RenderSystem *renderSystem;
    Window *gameWindow;
    ArrayList appLayerStack;

    ApplicationVersion version;
    bool isRunning;
    bool isInitialized;
}ClientApplication;

#ifdef MINECRAFT_CLIENT_APPLICATION_C
    static ClientApplication APP_STATE = {.isRunning=false, .isInitialized=false};
    static inline void ClientApplication_onUpdate();
    static inline void ClientApplication_onRender();
    static inline void ClientApplication_PollEvents();
    static inline void ClientApplciation_pollKeyboardInput();
    static inline void ClientApplciation_onMouseInput();
    
    static inline void ClientApplication_createGameWindow();
    
#endif


bool ClientApplication_create(ApplicationInfo appInfo);

void ClientApplication_run();

void ClientApplication_stop();

void ClientApplication_restart();

bool ClientApplication_isRunning();

bool ClientApplication_isInitialized();

bool ClientApplication_isReadyToRun();


ApplicationVersion ClientApplicaton_version();

Window* ClientApplication_getGameWindow();

void ClientApplication_pushLayer(ApplicationLayer layer);

ApplicationLayer* ClientApplication_getLayer(ApplicationLayerType layerType);

void ClientApplication_removeLayer(ApplicationLayerType layerType);

void ClientApplication_destroy();


#endif