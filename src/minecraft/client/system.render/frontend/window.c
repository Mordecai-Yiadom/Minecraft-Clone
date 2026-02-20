#include "window.h"

#define MINECRAFT_CLIENT_RENDER_SYSTEM_GL_CONTEXT_STD_VERSION_MAJOR 3
#define MINECRAFT_CLIENT_RENDER_SYSTEM_GL_CONTEXT_STD_VERSION_MINOR 3

Window Window_create(WindowProps props)
{   
    //Context Setup
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MINECRAFT_CLIENT_RENDER_SYSTEM_GL_CONTEXT_STD_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINECRAFT_CLIENT_RENDER_SYSTEM_GL_CONTEXT_STD_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    Window window;
    memset(&window, 0, sizeof(Window));

    window.glfwWindow = glfwCreateWindow(props.width, props.height, (const char*) props.title, NULL, NULL);

    //Context Setup
    glfwMakeContextCurrent(window.glfwWindow);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        Logger_logError(RENDER_SYSTEM, "GLAD failed to load OpenGL functions.");
        Window_destroy(&window);
        return window;
    }
    
    if(!window.glfwWindow)
    {   
        Logger_logError(RENDER_SYSTEM, "GLFW failed to create game window.");
        Window_destroy(&window);
        return window;
    }

    if(props.isFullscreen) Window_setFullscreen(&window, true);
    
    Window_setVsync(&window, props.isVsync);
    Window_setVisible(&window, props.isVisible);

    return window;
}

void Window_destroy(Window* window)
{
    if(!window) return;
    glfwSetWindowShouldClose(window->glfwWindow, 1);
    glfwDestroyWindow(window->glfwWindow);
}
 
void Window_setTitle(Window *window, char* title)
{   
    if(!window) return;
    glfwSetWindowTitle(window->glfwWindow, (const char*) title);
}

char* Window_getTitle(Window *window)
{   
    if(!window) return NULL;
    return (char*) glfwGetWindowTitle(window->glfwWindow);
}

void Window_setSize(Window *window, int width, int height)
{   
    if(!window) return;
    glfwSetWindowSize(window->glfwWindow, width, height);
}

void Window_getSize(Window *window, int *width, int *height)
{
    if(!window) return;
    glfwGetWindowSize(window->glfwWindow, width, height);
}

void Window_setVsync(Window* window, bool isVsync)
{   
    if(!window) return;
    glfwSwapInterval((int) isVsync);
    window->isVsync = isVsync;
}

bool Window_isVsync(Window *window)
{
    if(!window) return false;
    return window->isVsync;
}

void Window_setVisible(Window* window, bool isVisible)
{
    if(!window) return;
    if(isVisible) glfwShowWindow(window->glfwWindow);
    else glfwHideWindow(window->glfwWindow);
}

void Window_setFullscreen(Window* window, bool isFullscreen)
{
    if(!window) return;
    if(!window->glfwWindow) return;

    GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(primaryMonitor);
    
    int xPos, yPos;
    glfwGetMonitorPos(primaryMonitor, &xPos, &yPos);

    if(isFullscreen && !glfwGetWindowMonitor(window->glfwWindow))
        glfwSetWindowMonitor(window->glfwWindow, primaryMonitor, xPos, yPos, mode->width, mode->height, 0);
    else 
        glfwSetWindowMonitor(window->glfwWindow, (GLFWmonitor*) NULL, xPos, yPos, mode->width, mode->height, mode->refreshRate);
}

bool Window_isFullscreen(Window *window)
{
    if(!window) return false;
    return (bool) glfwGetWindowMonitor(window->glfwWindow);
}

bool Window_shouldClose(Window *window)
{
    if(!window) return false;
    return glfwWindowShouldClose(window->glfwWindow);
}

void Window_swapBuffers(Window *window)
{
    if(!window) return;
    glfwSwapBuffers(window->glfwWindow);
}

bool Window_isValid(Window *window)
{
    if(!window) return false;
    return (bool)(window->glfwWindow);
}

