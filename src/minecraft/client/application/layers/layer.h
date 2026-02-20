#ifndef MINECRAFT_CLIENT_LAYER_H
#define MINECRAFT_CLIENT_LAYER_H

typedef struct ApplicationLayer ApplicationLayer;
typedef enum ApplicationLayerType ApplicationLayerType;

#include "gamelayer.h"

typedef enum ApplicationLayerType
{
    GAME_LAYER,
}ApplicationLayerType;


typedef void(*AppLayerOnRender)(ApplicationLayer *layer);
typedef void(*AppLayerOnUpdate)(ApplicationLayer *layer);
typedef void(*AppLayerTransitionTo)(ApplicationLayer *layer, ApplicationLayerType newLayerType);
typedef void(*AppLayerSuspend)(ApplicationLayer *layer);
typedef bool(*AppLayerPollKeyboardInput)(ApplicationLayer *layer);
typedef bool(*AppLayerOnMouseInput)(ApplicationLayer *layer);


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
    AppLayerPollKeyboardInput pollKeyboardInput;
    AppLayerOnMouseInput onMouseInput;

    ApplicationLayerType type;
    bool isSuspended;
}ApplicationLayer;



#endif