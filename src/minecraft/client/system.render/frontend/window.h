#ifndef MINECRAFT_CLIENT_SYSTEM_WINDOW_H
#define MINECRAFT_CLIENT_SYSTEM_WINDOW_H


#include "../../../core/core.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define Window_PollEvents() glfwPollEvents()

typedef struct WindowProps
{
    char* title;
    int width;
    int height;
    bool isVisible;
    bool isVsync;
    bool isFullscreen;
}WindowProps;

typedef struct Window
{
    GLFWwindow* glfwWindow;
    bool isVsync;
}Window;

Window* Window_create(WindowProps props);

void Window_destroy(Window* window);

void Window_setTitle(Window *window, char* title);

char* Window_getTitle(Window *window);

void Window_setSize(Window *window, int width, int height);

void Window_getSize(Window *window, int *width, int *height);

void Window_setVsync(Window* window, bool isVsync);

bool Window_isVsync(Window *window);

void Window_setVisible(Window* window, bool isVisible);

bool Window_isVisible(Window *window);

void Window_setFullscreen(Window* window, bool isFullscreen);

bool Window_isFullscreen(Window *window);

void Window_setViewport(Window *window, int xOrigin, int yOrigin, int width, int height);

bool Window_shouldClose(Window *window);

void Window_swapBuffers(Window *window);



#endif
