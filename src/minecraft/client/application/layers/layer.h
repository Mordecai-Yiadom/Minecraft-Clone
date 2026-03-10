#ifndef MINECRAFT_CLIENT_LAYER_H
#define MINECRAFT_CLIENT_LAYER_H

typedef struct ApplicationLayer ApplicationLayer;
typedef enum ApplicationLayerType ApplicationLayerType;

#include "../event/event.h"

#include "gamelayer.h"

typedef enum ApplicationLayerType
{
    GAME_LAYER,
}ApplicationLayerType;


typedef void(*AppLayerOnRender)(ApplicationLayer *layer);
typedef void(*AppLayerOnUpdate)(ApplicationLayer *layer);
typedef void(*AppLayerTransitionTo)(ApplicationLayer *layer, ApplicationLayerType newLayerType);
typedef void(*AppLayerSuspend)(ApplicationLayer *layer);


typedef bool(*AppLayerPollKeyInput)(ApplicationLayer *layer, InputContext inputContext);
typedef bool(*AppLayerPollMouseInput)(ApplicationLayer *layer, InputContext inputContext);

//Events

typedef bool(*AppLayerOnMouseMove)(ApplicationLayer *layer, MouseMoveEvent event);
typedef bool(*AppLayerOnMouseButtonInput)(ApplicationLayer *layer, MouseButtonInputEvent event);
typedef bool(*AppLayerOnMouseScrollInput)(ApplicationLayer *layer, MouseScrollEvent event);

typedef bool(*AppLayerOnKeyInput)(ApplicationLayer *layer, KeyInputEvent event);


typedef struct ApplicationLayer
{   
    union 
    {
        GameLayerState gameLayerState;
    };

    AppLayerOnRender onRender;
    AppLayerOnUpdate onUpdate;
    AppLayerTransitionTo transitionTo;
    AppLayerSuspend suspend;

    AppLayerPollKeyInput pollKeyInput;
    AppLayerPollMouseInput pollMouseInput;

    AppLayerOnMouseMove onMouseMove;
    AppLayerOnMouseButtonInput onMouseButtonInput;
    AppLayerOnMouseScrollInput onMouseScrollInput;
    AppLayerOnKeyInput onKeyInput;

    ApplicationLayerType type;
    bool isSuspended;
}ApplicationLayer;



#endif