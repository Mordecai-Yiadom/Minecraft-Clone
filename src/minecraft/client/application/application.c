#define MINECRAFT_CLIENT_APPLICATION_C
#include "application.h"


bool ClientApplication_create(ApplicationInfo appInfo)
{
    if(ClientApplication_isInitialized())
    {
        //Logger_logError(APPLICATION_ERROR, "Failed to initialize ClientApplication as it is already initalized.");
        return false;
    }

    APP_STATE.appInfo = appInfo;

    APP_STATE.version = appInfo.version;
    APP_STATE.appLayerStack = ArrayList_create(10, sizeof(ApplicationLayer), DYNAMIC_MEMORY);

    APP_STATE.isInitialized = true;
    APP_STATE.windowIcon = Image_create("assets/minecraft/textures/gui/window-icon.png", false);
    return true;
}

//APP LOOP
void ClientApplication_run()
{   
    if(!ClientApplication_isReadyToRun())
    {
        //Logger_logError(APPLICATION_ERROR, "Failed to run ClientApplication as it is already running or not initalized.");
        return;
    }

    RenderSystem_init();

    APP_STATE.isRunning = true;
    
    ClientApplication_createGameWindow();


    //App Loop
    while(ClientApplication_isRunning())
    {   
        if(Window_shouldClose(&APP_STATE.gameWindow))
            ClientApplication_stop();
        
        ClientApplication_PollEvents();
        
        
        ClientApplication_onUpdate();
        ClientApplication_onRender();
        

        RenderSystem_update();

        Window_swapBuffers(&APP_STATE.gameWindow);
    }

}

void ClientApplication_stop()
{
    APP_STATE.isRunning = false;
    Window_close(&APP_STATE.gameWindow);
}

void ClientApplication_restart()
{}

bool ClientApplication_isRunning()
{
    return APP_STATE.isRunning;
}


bool ClientApplication_isInitialized()
{
    return APP_STATE.isInitialized;
}

bool ClientApplication_isReadyToRun()
{
    return ClientApplication_isInitialized() && !ClientApplication_isRunning();
}

ApplicationVersion ClientApplicaton_version()
{
    return APP_STATE.version;
}

Window* ClientApplication_getGameWindow()
{
    if(ClientApplication_isRunning())
        return &APP_STATE.gameWindow;
    else return NULL;
}

void ClientApplication_pushLayer(ApplicationLayer layer)
{
    if(!ClientApplication_isInitialized()) return;
    ArrayList_add(&APP_STATE.appLayerStack, (byte*)&layer);
}

ApplicationLayer* ClientApplication_getLayer(ApplicationLayerType layerType)
{
    if(!ClientApplication_isInitialized()) return NULL;

    ApplicationLayer currLayer;
    for(int i = 0; i < ArrayList_length(&APP_STATE.appLayerStack); i++)
    {   
        ArrayList_get(&APP_STATE.appLayerStack, i, (byte*)&currLayer);
        if(currLayer.type == layerType) 
            return (ApplicationLayer*) ArrayList_getAddress(&APP_STATE.appLayerStack, i);
    }

    return NULL;
}

void ClientApplication_removeLayer(ApplicationLayerType layerType)
{   
    ApplicationLayer currLayer;
    for(int i = 0; i < ArrayList_length(&APP_STATE.appLayerStack); i++)
    {   
        ArrayList_get(&APP_STATE.appLayerStack, i, (byte*)&currLayer);
        if(currLayer.type == layerType) 
        {
            ArrayList_remove(&APP_STATE.appLayerStack, i);
            return;
        }
    }
}

void ClientApplication_destroy()
{
    if(!ClientApplication_isReadyToRun()) return;
    ArrayList_destroy(&APP_STATE.appLayerStack);
    Window_destroy(&APP_STATE.gameWindow);
    Image_destroy(&APP_STATE.windowIcon);
    memset(&APP_STATE, 0, sizeof(ClientApplication));
}


static inline void ClientApplication_onUpdate()
{    
    ApplicationLayer currLayer;
    for(int i = 0; i < ArrayList_length(&APP_STATE.appLayerStack); i++)
    {   
        ArrayList_get(&APP_STATE.appLayerStack, i, (byte*)&currLayer);
        if(currLayer.isSuspended) continue;
        if(currLayer.onUpdate)
        {   
            currLayer.onUpdate(&currLayer);
        }
    }
}

static inline void ClientApplication_onRender()
{
    ApplicationLayer currLayer;
    for(int i = 0; i < ArrayList_length(&APP_STATE.appLayerStack); i++)
    {
        ArrayList_get(&APP_STATE.appLayerStack, i, (byte*)&currLayer);
        if(currLayer.isSuspended) continue;

        if(currLayer.onRender)
        {
            currLayer.onRender(&currLayer);
        }
    }
}

static inline void ClientApplication_PollEvents()
{
    Window_PollEvents();
    ClientApplication_pollKeyInput();
    ClientApplication_pollMouseInput();
    
}

static inline void ClientApplication_pollKeyInput()
{
    ApplicationLayer currLayer;
    for(int i = ArrayList_length(&APP_STATE.appLayerStack) - 1; i >= 0; i--)
    {
        ArrayList_get(&APP_STATE.appLayerStack, i, (byte*)&currLayer);
        if(currLayer.isSuspended) continue;

        if(currLayer.pollKeyInput)
        {
            currLayer.pollKeyInput(&currLayer, APP_STATE.inputContext);
        }
    }  
}

static inline void ClientApplication_pollMouseInput()
{
    ApplicationLayer currLayer;
    for(int i = ArrayList_length(&APP_STATE.appLayerStack) - 1; i >= 0; i--)
    {
        ArrayList_get(&APP_STATE.appLayerStack, i, (byte*)&currLayer);
        if(currLayer.isSuspended) continue;

        if(currLayer.pollMouseInput)
        {
            currLayer.pollMouseInput(&currLayer, APP_STATE.inputContext);
        }
    }  
}


static inline void ClientApplication_createGameWindow()
{   
    if(Window_isValid(&APP_STATE.gameWindow))
    {   
        //Logger_logError(APPLICATION_ERROR, "Failed to create ClientApplication Game Window as a valid instance already exists.");
        return;
    }

    APP_STATE.gameWindow = Window_create(APP_STATE.appInfo.windowProps);
    Window_setIcon(&APP_STATE.gameWindow, &APP_STATE.windowIcon);

    APP_STATE.inputContext = InputContext_create(APP_STATE.gameWindow.glfwWindow);

    //Setup Event dispatchers
    MouseButtonInputEvent_setDispatcher(APP_STATE.inputContext, ClientApplication_dispatchOnMouseButtonInputEventAsync);
    MouseMoveEvent_setDispatcher(APP_STATE.inputContext, ClientApplication_dispatchOnMouseMoveEventAsync);
    MouseScrollEvent_setDispatcher(APP_STATE.inputContext, ClientApplication_dispatchOnMouseScrollEventAsync);
    
    KeyInputEvent_setDispatcher(APP_STATE.inputContext, ClientApplication_dispatchOnKeyInputEventAsync);
}


//TESTING ONLY - REMOVE 
void* logInfo()
{   
    puts("Hello World");
    return NULL;
}


void ClientApplication_dispatchOnMouseMoveEventAsync(GLFWwindow *window, double xPos, double yPos)
{   
    MouseMoveEvent event = {.xPos=xPos, .yPos=yPos, .context=((InputContext){.glfwWindow=window})};

    ApplicationLayer currLayer;
    bool isHandled = false;
    for(int i = ArrayList_length(&APP_STATE.appLayerStack) - 1; i >= 0; i--)
    {
        ArrayList_get(&APP_STATE.appLayerStack, i, (byte*)&currLayer);
        if(currLayer.onMouseMove == NULL || currLayer.isSuspended) continue;   
        
        isHandled = currLayer.onMouseMove(&currLayer, event);
        if(isHandled) return;
    }  
}

void ClientApplication_dispatchOnMouseScrollEventAsync(GLFWwindow *window, double xOffset, double yOffset)
{
    MouseScrollEvent event = {.xOffset=xOffset, .yOffset=yOffset, .context=((InputContext){.glfwWindow=window})};

    ApplicationLayer currLayer;
    bool isHandled = false;
    for(int i = ArrayList_length(&APP_STATE.appLayerStack) - 1; i >= 0; i--)
    {
        ArrayList_get(&APP_STATE.appLayerStack, i, (byte*)&currLayer);

        if(!(currLayer.onMouseScrollInput) || currLayer.isSuspended) continue;   

        isHandled = currLayer.onMouseScrollInput(&currLayer, event);
        if(isHandled) return;
    }  
}

void ClientApplication_dispatchOnMouseButtonInputEventAsync(GLFWwindow *window, int button, int action, int mods)
{
    MouseButtonInputEvent event = {.button=button, .action=action, .modifiers=mods, .context=((InputContext){.glfwWindow=window})};

    ApplicationLayer currLayer;
    bool isHandled = false;
    for(int i = ArrayList_length(&APP_STATE.appLayerStack) - 1; i >= 0; i--)
    {
        ArrayList_get(&APP_STATE.appLayerStack, i, (byte*)&currLayer);

        if(!(currLayer.onMouseButtonInput) || currLayer.isSuspended) continue;   

        isHandled = currLayer.onMouseButtonInput(&currLayer, event);
        if(isHandled) return;
    }    
}

void ClientApplication_dispatchOnKeyInputEventAsync(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    KeyInputEvent event = {.key=key, .scancode=scancode, .action=action, .modifiers=mods, .context=((InputContext){.glfwWindow=window})};

    ApplicationLayer currLayer;
    bool isHandled = false;
    for(int i = ArrayList_length(&APP_STATE.appLayerStack) - 1; i >= 0; i--)
    {
        ArrayList_get(&APP_STATE.appLayerStack, i, (byte*)&currLayer);

        if(!(currLayer.onKeyInput) || currLayer.isSuspended) continue;   

        isHandled = currLayer.onKeyInput(&currLayer, event);
        if(isHandled) return;
    }    
}