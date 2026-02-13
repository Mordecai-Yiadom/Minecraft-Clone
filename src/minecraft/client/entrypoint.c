#include "application/application.h"
#include <stdio.h>

int main(void)
{   
    WindowProps windowProps 
    = {.height=720, 
        .width=1280, 
        .isFullscreen=false, 
        .isVisible=true, 
        .title="Minecraft"};

    ApplicationInfo info = {.props=windowProps};
    if(!MinecraftClientApplication_create(&info))
    {
        Logger_logError(APPLICATION_ERROR, "Failed to create Client Application instance.");
        exit(-1);
    }

    MinecraftClientApplication_launch();
    MinecraftClientApplication_terminate();
    return 0;
}