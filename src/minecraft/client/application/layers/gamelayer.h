#ifndef MINECRAFT_CLIENT_GAMELAYER_H
#define MINECRAFT_CLIENT_GAMELAYER_H

#include "../../system.render/rendersystem.h"


typedef struct GameLayerState
{
    Camera camera;
}GameLayerState;

#include "layer.h"

ApplicationLayer GameLayer_create(GameLayerState state);

void GameLayer_destroy(ApplicationLayer *gamelayer);

void GameLayer_destroy(ApplicationLayer *gamelayer);

void GameLayer_onRender(ApplicationLayer *gamelayer);

void GameLayer_onUpdate(ApplicationLayer *gamelayer);

void GameLayer_transitionTo(ApplicationLayer *gamelayer, ApplicationLayerType newLayerType);

void GameLayer_suspend(ApplicationLayer *gamelayer);

bool GameLayer_processKeyboardInput(ApplicationLayer *gamelayer);

bool GameLayer_onMouseInput(ApplicationLayer *gamelayer);

#endif