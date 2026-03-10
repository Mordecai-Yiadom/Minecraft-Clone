#ifndef MINECRAFT_CLIENT_MOUSEINPUTEVENT_H
#define MINECRAFT_CLIENT_MOUSEINPUTEVENT_H

#include "../../system.input/inputsystem.h"

typedef struct MouseMoveEvent
{   
    InputContext context;
    double xPos;
    double yPos;
}MouseMoveEvent;

typedef struct MouseScrollEvent
{   
    InputContext context;
    double xOffset;
    double yOffset;
}MouseScrollEvent;

typedef struct MouseButtonInputEvent
{   
    InputContext context;
    MouseButton button;
    MouseButtonAction action;
    InputModifier modifiers;
}MouseButtonInputEvent;

void MouseMoveEvent_setDispatcher(InputContext context, void* dispatcher);

void MouseScrollEvent_setDispatcher(InputContext context, void* dispatcher);

void MouseButtonInputEvent_setDispatcher(InputContext context, void* dispatcher);


#endif