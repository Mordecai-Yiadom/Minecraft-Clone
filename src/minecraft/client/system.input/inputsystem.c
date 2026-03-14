#include "inputsystem.h"

InputContext InputContext_create(GLFWwindow *glfwWindow)
{
    return (InputContext){.glfwWindow = glfwWindow};
}

void InputContext_setMouseInputMode(InputContext inputContext, MouseInputMode mode)
{
    glfwSetInputMode(inputContext.glfwWindow, GLFW_CURSOR, mode);
}

MouseInputMode InputContext_getMouseInputMode(InputContext inputContext)
{
    return (MouseInputMode) glfwGetInputMode(inputContext.glfwWindow, GLFW_CURSOR);
}

KeyAction InputContext_getKeyAction(InputContext inputContext, Key key)
{
    return (KeyAction) (glfwGetKey(inputContext.glfwWindow, key));
}

void InputContext_doRawMouseInput(InputContext inputContext, bool doRawMouseInput)
{
    glfwSetInputMode(inputContext.glfwWindow, GLFW_RAW_MOUSE_MOTION, doRawMouseInput);
}

bool InputContext_isRawMouseInput(InputContext inputContext)
{
    return (bool)(glfwGetInputMode(inputContext.glfwWindow, GLFW_RAW_MOUSE_MOTION));
}