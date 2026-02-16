#ifndef MINECRAFT_CLIENT_GAMELAYER_H
#define MINECRAFT_CLIENT_GAMELAYER_H

#include "../../system.render/rendersystem.h"
#include "layer.h"

typedef struct GameLayerState
{
    Camera camera;
}GameLayerState;

ApplicationLayer GameLayer_create(GameLayerState state);

void GameLayer_destroy(ApplicationLayer *gamelayer);

void GameLayer_destroy(ApplicationLayer *gamelayer);

void GameLayer_onRender(ApplicationLayer *gamelayer);

void GameLayer_onTransition(ApplicationLayer *gamelayer);

void GameLayer_onSuspend(ApplicationLayer *gamelayer);

bool GameLayer_processKeyboardInput(ApplicationLayer *gamelayer);

bool GameLayer_onMouseInput(ApplicationLayer *gamelayer);

#endif