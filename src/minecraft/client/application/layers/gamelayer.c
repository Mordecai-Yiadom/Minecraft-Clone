#include "gamelayer.h"

ApplicationLayer GameLayer_create(GameLayerState state)
{
    ApplicationLayer gamelayer;
    gamelayer.gameLayerState = state;
    gamelayer.type = GAME_LAYER;
    gamelayer.isSuspended = false;

    gamelayer.onRender = GameLayer_onRender;
    gamelayer.transitionTo = GameLayer_transitionTo;
    gamelayer.suspend = GameLayer_suspend;
    gamelayer.pollKeyboardInput = GameLayer_pollKeyboardInput;
    gamelayer.onMouseInput = GameLayer_onMouseInput;
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

void GameLayer_onUpdate(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return;
}

void GameLayer_transitionTo(ApplicationLayer *gamelayer, ApplicationLayerType newLayerType)
{
    if(!gamelayer || newLayerType == GAME_LAYER) return;
}

void GameLayer_suspend(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return;
}

bool GameLayer_pollKeyboardInput(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return false;
    return true;
}

bool GameLayer_onMouseInput(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return false;
    return true;
}
