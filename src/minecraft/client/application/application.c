#include "application.h"


static MinecraftClientApplication *MINECRAFT_CLIENT_APPLICATION_INSTANCE = NULL;


bool MinecraftClientApplication_create(ApplicationInfo *appInfo)
{   
    if(!appInfo) 
    {
        Logger_logError(APPLICATION_ERROR, "Failed to create Client Application. Null AppInfo passed.");
        return false;
    }

    if(MINECRAFT_CLIENT_APPLICATION_INSTANCE)
    {
        Logger_logError(APPLICATION_ERROR, "Failed to create Client Application. Instance already is running.");
        return false;
    }

    MINECRAFT_CLIENT_APPLICATION_INSTANCE = (MinecraftClientApplication*) malloc(sizeof(MinecraftClientApplication));
    
    RenderSystem_init();
    MINECRAFT_CLIENT_APPLICATION_INSTANCE->gameWindow = Window_create(appInfo->props);

    if(!MINECRAFT_CLIENT_APPLICATION_INSTANCE->gameWindow)
    {   
        Logger_logError(APPLICATION_ERROR, "Failed to create Client Application. Game Window failed to initialize.");
        return false;
    }

    return true;
}

void MinecraftClientApplication_launch()
{
    if(!MINECRAFT_CLIENT_APPLICATION_INSTANCE)
    {
        Logger_logError(APPLICATION_ERROR, "Client Application failed to launch.");
        return;
    }
    
    MINECRAFT_CLIENT_APPLICATION_INSTANCE->isRunning = true;

    Window_setVisible(MINECRAFT_CLIENT_APPLICATION_INSTANCE->gameWindow, true);

    //Game Loop
    char titleBuffer[48];
    
    while(MINECRAFT_CLIENT_APPLICATION_INSTANCE->isRunning)
    {   
        if(Window_shouldClose(MINECRAFT_CLIENT_APPLICATION_INSTANCE->gameWindow)) 
            MINECRAFT_CLIENT_APPLICATION_INSTANCE->isRunning = false;

        RenderSystem_startRenderPass();
        RenderSystem_endRenderPass(MINECRAFT_CLIENT_APPLICATION_INSTANCE->gameWindow);
        
        memset(titleBuffer, 0, sizeof(titleBuffer));
        sprintf(titleBuffer, "Minecraft (FPS: %d)", FPS());    
        Window_setTitle(MINECRAFT_CLIENT_APPLICATION_INSTANCE->gameWindow, titleBuffer);
        
        Window_PollEvents();
    }
}


void MinecraftClientApplication_terminate()
{   
    if(!MINECRAFT_CLIENT_APPLICATION_INSTANCE) return;
    Window_destroy(MINECRAFT_CLIENT_APPLICATION_INSTANCE->gameWindow);
    free(MINECRAFT_CLIENT_APPLICATION_INSTANCE);
    MINECRAFT_CLIENT_APPLICATION_INSTANCE = NULL;
}