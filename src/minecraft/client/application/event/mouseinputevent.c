#include "mouseinputevent.h"

void MouseMoveEvent_setDispatcher(InputContext context, void* dispatcher)
{
    if(!dispatcher) return;
    glfwSetCursorPosCallback(context.glfwWindow, dispatcher);
}

void MouseScrollEvent_setDispatcher(InputContext context, void* dispatcher)
{
    if(!dispatcher) return;
    glfwSetScrollCallback(context.glfwWindow, dispatcher);
}

void MouseButtonInputEvent_setDispatcher(InputContext context, void* dispatcher)
{
    if(!dispatcher) return;
    glfwSetMouseButtonCallback(context.glfwWindow, dispatcher);
}
