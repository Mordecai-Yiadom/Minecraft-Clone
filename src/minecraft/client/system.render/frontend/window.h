#ifndef MINECRAFT_CLIENT_SYSTEM_WINDOW_H
#define MINECRAFT_CLIENT_SYSTEM_WINDOW_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct WindowProps
{
    
}WindowProps;

typedef struct Window
{
    GLFWwindow* window;

}Window;

Window* Window_create();
Window* Window_destroy();

#endif
