#ifndef MINECRAFT_CLIENT_INPUT_SYSTEM_H
#define MINECRAFT_CLIENT_INPUT_SYSTEM_H

#include "../system.render/frontend/window.h"
#include <stdbool.h>
typedef enum Key
{
    KEY_W = GLFW_KEY_W,
    KEY_A = GLFW_KEY_A,
    KEY_S = GLFW_KEY_S,
    KEY_D = GLFW_KEY_D,
    KEY_ESC = GLFW_KEY_ESCAPE
}Key;

typedef enum KeyAction
{
    KEY_PRESS = GLFW_PRESS,
    KEY_RELEASE = GLFW_RELEASE,
    KEY_REPEAT = GLFW_REPEAT,
}KeyAction;

typedef enum InputModifier
{
    MOD_SHIFT = GLFW_MOD_SHIFT,
    MOD_CONTROL = GLFW_MOD_CONTROL,
    MOD_ALT = GLFW_MOD_ALT,
    MOD_SUPER = GLFW_MOD_SUPER,
    MOD_CAPS_LOCK = GLFW_MOD_CAPS_LOCK,
    MOD_NUM_LOCK = GLFW_MOD_NUM_LOCK
}InputModifier;


typedef enum MouseButton
{
    MOUSE_BUTTON_LEFT = GLFW_MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
    MOUSE_BUTTON_4 = GLFW_MOUSE_BUTTON_4,
    MOUSE_BUTTON_5 = GLFW_MOUSE_BUTTON_5,
    MOUSE_BUTTON_6 = GLFW_MOUSE_BUTTON_6,
    MOUSE_BUTTON_7 = GLFW_MOUSE_BUTTON_7,
    MOUSE_BUTTON_8 = GLFW_MOUSE_BUTTON_8,
}MouseButton;

typedef enum MouseButtonAction
{
    MOUSE_BUTTON_PRESS = GLFW_PRESS,
    MOUSE_BUTTON_RELEASE = GLFW_RELEASE,
}MouseButtonAction;

typedef enum MouseInputMode
{
    MOUSE_NORMAL = GLFW_CURSOR_NORMAL,
    MOUSE_HIDDEN = GLFW_CURSOR_HIDDEN,
    MOUSE_HIDDEN_AND_CAPTURED = GLFW_CURSOR_DISABLED,
    MOUSE_CAPTURED = GLFW_CURSOR_CAPTURED
}MouseInputMode;

typedef struct InputContext
{   
    GLFWwindow *glfwWindow; 
}InputContext;


void InputSystem_init();
InputContext InputContext_create(GLFWwindow *glfwWindow);

void InputContext_setMouseInputMode(InputContext inputContext, MouseInputMode mode);

MouseInputMode InputContext_getMouseInputMode(InputContext inputContext, MouseInputMode mode);

KeyAction InputContext_getKeyAction(InputContext inputContext, Key key);

void InputContext_doRawMouseInput(InputContext inputContext, bool doRawMouseInput);

bool InputContext_isRawMouseInput(InputContext inputContext);


#ifdef MINECRAFT_CLIENT_INPUT_SYSTEM_C
    
#endif



#endif