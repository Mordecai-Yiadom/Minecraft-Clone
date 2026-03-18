#ifndef MINECRAFT_CLIENT_GAMELAYER_H
#define MINECRAFT_CLIENT_GAMELAYER_H

#include "../../system.render/rendersystem.h"

#include "../../../core/core.h"

typedef struct GameLayerState
{
    Camera *mainCamera;
    World world;
}GameLayerState;

#include "layer.h"

ApplicationLayer GameLayer_create(GameLayerState state);

void GameLayer_destroy(ApplicationLayer *gamelayer);

void GameLayer_destroy(ApplicationLayer *gamelayer);

void GameLayer_onRender(ApplicationLayer *gamelayer);

void GameLayer_onUpdate(ApplicationLayer *gamelayer);

void GameLayer_transitionTo(ApplicationLayer *gamelayer, ApplicationLayerType newLayerType);

void GameLayer_suspend(ApplicationLayer *gamelayer);


bool GameLayer_pollKeyInput(ApplicationLayer *gamelayer, InputContext inputContext);

bool GameLayer_pollMouseInput(ApplicationLayer *gamelayer, InputContext inputContext);


bool GameLayer_onMouseMove(ApplicationLayer *gamelayer, MouseMoveEvent event);

bool GameLayer_onMouseButtonInput(ApplicationLayer *gamelayer, MouseButtonInputEvent event);

bool GameLayer_onMouseScrollInput(ApplicationLayer *gamelayer, MouseScrollEvent event);

bool GameLayer_onKeyInput(ApplicationLayer *gamelayer, KeyInputEvent event);

Camera* GameLayer_getMainCamera();
#endif