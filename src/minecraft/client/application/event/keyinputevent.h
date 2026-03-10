#ifndef MINECRAFT_CLIENT_KEYINPUT_EVENT_H
#define MINECRAFT_CLIENT_KEYINPUT_EVENT_H

#include "../../system.input/inputsystem.h"

typedef struct KeyInputEvent
{   
    InputContext context;
    Key key;
    int scancode;
    KeyAction action;
    InputModifier modifiers;
}KeyInputEvent;

void KeyInputEvent_setDispatcher(InputContext context, void* dispatcher);




#endif