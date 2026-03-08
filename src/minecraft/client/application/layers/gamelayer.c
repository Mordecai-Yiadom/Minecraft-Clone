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
    gamelayer.pollKeyboardInput = GameLayer_pollKeyboardInput;
    gamelayer.onMouseInput = GameLayer_onMouseInput;
    gamelayer.onUpdate = GameLayer_onUpdate;
    return gamelayer;
}

void GameLayer_destroy(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return;
}

void GameLayer_onRender(ApplicationLayer *gamelayer)
{   
    if(!gamelayer) return;
    ChunkMesh mesh;
    ChunkRenderer_drawChunkMesh(&mesh);
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

bool GameLayer_pollKeyboardInput(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return false;

    if(glfwGetKey(ClientApplication_getGameWindow()->glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        ClientApplication_stop();
    }

    return true;
}

bool GameLayer_onMouseInput(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return false;
    return true;
}
