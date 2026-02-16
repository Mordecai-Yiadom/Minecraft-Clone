#ifndef MINECRAFT_CLIENT_LAYERTYPES_H
#define MINECRAFT_CLIENT_LAYERTYPES_H

#include "gamelayer.h"

typedef enum AppLayerType
{
    GAME_LAYER,
}AppLayerType;

typedef union AppLayerState
{
    GameLayerState gamelayer;
}AppLayerState;


#endif