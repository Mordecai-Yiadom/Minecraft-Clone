#include "gamelayer.h"

ApplicationLayer GameLayer_create(GameLayerData data)
{
    ApplicationLayer gamelayer;
    gamelayer.data.gamelayer = data;
    gamelayer.type = GAME_LAYER;
    gamelayer.isSuspended = false;

    gamelayer.onRender = GameLayer_onRender;
    gamelayer.onTransition = GameLayer_onTransition;
    gamelayer.onSuspend = GameLayer_onSuspend;
    gamelayer.processMouseInput = GameLayer_processKeyboardInput;
    return gamelayer;
}

void GameLayer_destroy(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return;
}

void GameLayer_onRender(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return;
}

void GameLayer_onTransition(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return;
}

void GameLayer_onSuspend(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return;
}

bool GameLayer_processKeyboardInput(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return false;
    return true;
}

bool GameLayer_onMouseInput(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return false;
    return true;
}
