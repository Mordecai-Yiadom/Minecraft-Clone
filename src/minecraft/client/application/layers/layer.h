#ifndef MINECRAFT_CLIENT_LAYER_H
#define MINECRAFT_CLIENT_LAYER_H

typedef struct ApplicationLayer ApplicationLayer;

#include "layertypes.h"


typedef void(*AppLayerOnRender)(ApplicationLayer *layer);
typedef void(*AppLayerOnTransition)(ApplicationLayer *layer);
typedef void(*AppLayerOnSuspend)(ApplicationLayer *layer);
typedef bool(*AppLayerProcessKeyboardInput)(ApplicationLayer *layer);
typedef bool(*AppLayerOnMouseInput)(ApplicationLayer *layer);


typedef struct ApplicationLayer
{   
    AppLayerState layerState;
    AppLayerType type;

    AppLayerOnRender onRender;
    AppLayerOnTransition onTransition;
    AppLayerOnSuspend onSuspend;
    AppLayerProcessKeyboardInput processMouseInput;
    AppLayerOnMouseInput onMouseInput;

    bool isSuspended;
}ApplicationLayer;



#endif