#include "gamelayer.h"

#include "../../system.render/backend/backend.h"
#include "../../system.render/rendersystem.h"
#include "../../system.render/renderer.h"

#include "../application.h"
#include "../../system.render/renderers/chunkrenderer.h"

ApplicationLayer GameLayer_create(GameLayerState state)
{
    ApplicationLayer gamelayer;
    memset(&gamelayer, 0, sizeof(ApplicationLayer));

    gamelayer.gameLayerState = state;
    gamelayer.type = GAME_LAYER;
    gamelayer.isSuspended = false;

    gamelayer.onRender = GameLayer_onRender;
    gamelayer.transitionTo = GameLayer_transitionTo;
    gamelayer.suspend = GameLayer_suspend;
    gamelayer.onKeyInput = GameLayer_onKeyInput;
    //gamelayer.onMouseInput = GameLayer_onMouseInput;
    gamelayer.onUpdate = GameLayer_onUpdate;

    //gamelayer.gameLayerState.world = World_create(-193013);

    return gamelayer;
}

void GameLayer_destroy(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return;
}

void GameLayer_onRender(ApplicationLayer *gamelayer)
{   
    if(!gamelayer) return;

    ChunkRenderer_drawChunkMesh();
}

void GameLayer_onUpdate(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return;
    Transform3D transform;
    Quad_create(transform);
    ChunkRenderer_init();
}

void GameLayer_transitionTo(ApplicationLayer *gamelayer, ApplicationLayerType newLayerType)
{
    if(!gamelayer || newLayerType == GAME_LAYER) return;
}

void GameLayer_suspend(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return;
}


// bool GameLayer_pollKeyInput(ApplicationLayer *gamelayer, InputContext inputContext)
// {

// }



bool GameLayer_onKeyInput(ApplicationLayer *gamelayer, KeyInputEvent event)
{
    if(!gamelayer) return false;

    switch(event.key)
    {
        case KEY_ESC:
            if(event.action == KEY_PRESS) ClientApplication_stop();
            break;
        default:
            return false;
    }

    return true;
}

// bool GameLayer_onMouseMove(ApplicationLayer *gamelayer, MouseMoveEvent event)
// {
//     if(!gamelayer) return false;
//     return false;
// }

// bool GameLayer_onMouseButtonInput(ApplicationLayer *gamelayer, MouseButtonInputEvent event)
// {
//     if(!gamelayer) return false;
//     return false;
// }

// bool GameLayer_onMouseScrollInput(ApplicationLayer *gamelayer, MouseScrollEvent event)
// {
//     if(!gamelayer) return false;
//     return false;
// }

