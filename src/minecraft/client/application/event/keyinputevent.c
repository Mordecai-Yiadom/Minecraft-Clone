#include "keyinputevent.h"

void KeyInputEvent_setDispatcher(InputContext context, void* dispatcher)
{
    if(!dispatcher) return;
    glfwSetKeyCallback(context.glfwWindow, dispatcher);
}