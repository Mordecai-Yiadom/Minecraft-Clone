#ifndef MINECRAFT_CLIENT_APPLICATION_H
#define MINECRAFT_CLIENT_APPLICATION_H

#include "layers/layer.h"
#include "../system.render/rendersystem.h"
#include "event/event.h"

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
    Window gameWindow;
    InputContext inputContext;
    ArrayList appLayerStack;

    Image windowIcon;
    ApplicationVersion version;
    bool isRunning;
    bool isInitialized;
}ClientApplication;

#ifdef MINECRAFT_CLIENT_APPLICATION_C
    static ClientApplication APP_STATE = {.isRunning=false, .isInitialized=false};
    static inline void ClientApplication_onUpdate();
    static inline void ClientApplication_onRender();
    static inline void ClientApplication_PollEvents();

    
    static inline void ClientApplication_pollKeyInput();
    static inline void ClientApplication_pollMouseInput();
    
    static inline void ClientApplication_createGameWindow();

    void ClientApplication_dispatchOnMouseMoveEventAsync(GLFWwindow *window, double xPos, double yPos);
    void ClientApplication_dispatchOnMouseScrollEventAsync(GLFWwindow *window, double xOffset, double yOffset);
    void ClientApplication_dispatchOnMouseButtonInputEventAsync(GLFWwindow *window, int button, int action, int mods);
    void ClientApplication_dispatchOnKeyInputEventAsync(GLFWwindow *window, int key, int scancode, int action, int mods);
    
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