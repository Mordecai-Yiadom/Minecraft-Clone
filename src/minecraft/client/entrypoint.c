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
    if(!ClientApplication_create(info))
    {
        Logger_logError(APPLICATION_ERROR, "Failed to create Client Application instance.");
        exit(-1);
    }

    ClientApplication_launch();
    ClientApplication_terminate();
    return 0;
}