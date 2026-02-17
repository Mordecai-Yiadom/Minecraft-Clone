#include "application.h"


static ClientApplication CLIENTAPPLICATION_INSTANCE = {.isRunning=false, .isInitialized=false};


bool ClientApplication_create(ApplicationInfo appInfo)
{   
    if(CLIENTAPPLICATION_INSTANCE.isRunning)
    {
        Logger_logError(APPLICATION_ERROR, "Failed to create Client Application. Instance already is running.");
        return false;
    }

    RenderSystem_init();
    CLIENTAPPLICATION_INSTANCE.gameWindow = Window_create(appInfo.props);

    if(!CLIENTAPPLICATION_INSTANCE.gameWindow)
    {   
        Logger_logError(APPLICATION_ERROR, "Failed to create Client Application. Game Window failed to initialize.");
        return false;
    }

    CLIENTAPPLICATION_INSTANCE.isInitialized = true;
    return true;
}

void ClientApplication_launch()
{
    if(CLIENTAPPLICATION_INSTANCE.isRunning || !CLIENTAPPLICATION_INSTANCE.isInitialized)
    {
        Logger_logError(APPLICATION_ERROR, "Client Application failed to launch.");
        return;
    }
    
    CLIENTAPPLICATION_INSTANCE.isRunning = true;

    Window_setVisible(CLIENTAPPLICATION_INSTANCE.gameWindow, true);

    //Game Loop
    char titleBuffer[48];
    
    while(CLIENTAPPLICATION_INSTANCE.isRunning)
    {   
        if(Window_shouldClose(CLIENTAPPLICATION_INSTANCE.gameWindow)) 
            CLIENTAPPLICATION_INSTANCE.isRunning = false;

        Window_PollEvents();

        RenderSystem_startRenderPass();
        RenderSystem_endRenderPass(CLIENTAPPLICATION_INSTANCE.gameWindow);
        
        memset(titleBuffer, 0, sizeof(titleBuffer));
        sprintf(titleBuffer, "Minecraft (FPS: %d)", FPS());    
        Window_setTitle(CLIENTAPPLICATION_INSTANCE.gameWindow, titleBuffer);
        
    }
}


void ClientApplication_terminate()
{   
    if(!CLIENTAPPLICATION_INSTANCE.isInitialized) return;
    Window_destroy(CLIENTAPPLICATION_INSTANCE.gameWindow);
    
    CLIENTAPPLICATION_INSTANCE.isInitialized = false;
}