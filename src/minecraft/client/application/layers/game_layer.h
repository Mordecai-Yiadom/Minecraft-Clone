#ifndef MINECRAFT_CLIENT_GAME_LAYER_H
#define MINECRAFT_CLIENT_GAME_LAYER_H

#include "../../system.render/rendersystem.h"
#include "layer.h"

typedef struct GameLayerData
{
    Camera camera;
}GameLayerData;

ApplicationLayer GameLayer_create(GameLayerData data);
void GameLayer_destroy(ApplicationLayer *gamelayer);

AppLayerOnRender GameLayer_onRender();
AppLayerOnTransition GameLayer_onTransition();
AppLayerOnSuspend GameLayer_onSuspend();
AppLayerOnKeyboardInput GameLayer_onKeyboardInput();

#endif