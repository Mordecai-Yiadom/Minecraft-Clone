#ifndef MINECRAFT_CLIENT_LAYER_H
#define MINECRAFT_CLIENT_LAYER_H

#include "game_layer.h"

typedef void(*AppLayerOnRender)();
typedef void(*AppLayerOnTransition)();
typedef void(*AppLayerOnSuspend)();
typedef void(*AppLayerOnKeyboardInput)();

typedef union AppLayerData
{
    GameLayerData gamelayer;
}AppLayerData;

typedef struct ApplicationLayer
{   
    AppLayerData data;

    AppLayerOnRender onRender;
    AppLayerOnTransition onTransition;
    AppLayerOnSuspend onSuspend;
    AppLayerOnKeyboardInput onKeyboardInput;
}ApplicationLayer;



#endif