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

    ApplicationInfo info = {.windowProps=windowProps};
    if(!ClientApplication_create(info))
    {
        Logger_logError(APPLICATION_ERROR, "Failed to create Client Application instance.");
        exit(-1);
    }

    ClientApplication_run();
    ClientApplication_stop();
    ClientApplication_destroy();
    return 0;
}