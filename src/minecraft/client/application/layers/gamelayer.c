#include "gamelayer.h"

#include "../../system.render/backend/backend.h"
#include "../../system.render/rendersystem.h"
#include "../../system.render/renderer.h"

#include "../application.h"
#include "../../system.render/renderers/chunkrenderer.h"
static Camera* GAMELAYER_MAIN_CAMERA;
static World *world;

#define X_CHUNK_RENDER_DISTANCE 2
#define Z_CHUNK_RENDER_DISTANCE 2

static ChunkMesh renderedChunks[X_CHUNK_RENDER_DISTANCE][Z_CHUNK_RENDER_DISTANCE];

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
    gamelayer.onMouseMove = GameLayer_onMouseMove;
    gamelayer.onUpdate = GameLayer_onUpdate;
    gamelayer.pollKeyInput = GameLayer_pollKeyInput;

    //gamelayer.gameLayerState.world = World_create(-193013);
    GAMELAYER_MAIN_CAMERA = NULL;
    return gamelayer;
}

void GameLayer_destroy(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return;
}

void GameLayer_onRender(ApplicationLayer *gamelayer)
{   
    if(!gamelayer) return;
    

    for(int x = 0; x < X_CHUNK_RENDER_DISTANCE; x++)
    {
        for(int z = 0; z < Z_CHUNK_RENDER_DISTANCE; z++)
        {   
            ChunkRenderer_drawChunkMesh(&renderedChunks[x][z]);
        }
    }    
}

void GameLayer_onUpdate(ApplicationLayer *gamelayer)
{   
    if(!gamelayer) return;

    ChunkRenderer_init();
    
    
    if(!GAMELAYER_MAIN_CAMERA)
    {   
        GAMELAYER_MAIN_CAMERA = ChunkRenderer_getRenderTargetCamera();
        vec3 cameraSpeed;
        vec3f(cameraSpeed, 15, 15, 15);
        Camera_setSpeed(GAMELAYER_MAIN_CAMERA, cameraSpeed);

        world = World_create(0);

        BlockMesh_init();
        for(int x = 0; x < X_CHUNK_RENDER_DISTANCE; x++)
        {
            for(int z = 0; z < Z_CHUNK_RENDER_DISTANCE; z++)
            {   
                World_loadChunk(world, CHUNKINDEX(x, z)); 
            }
        }

        //Build create and build all chunks
        for(int x = 0; x < X_CHUNK_RENDER_DISTANCE; x++)
        {
            for(int z = 0; z < Z_CHUNK_RENDER_DISTANCE; z++)
            {   
                renderedChunks[x][z] = ChunkMesh_create(World_getChunk(world, CHUNKINDEX(x, z)));
                ChunkMesh_build(&renderedChunks[x][z]); 
            }
        }
    } 

    //Update FPS on Window bar
    static char fpsBuffer[32];
    sprintf(fpsBuffer, "FPS: %d", RenderSystem_fps());
    Window_setTitle(ClientApplication_getGameWindow(), fpsBuffer);
    memset(fpsBuffer, 0, sizeof(fpsBuffer));

}

void GameLayer_transitionTo(ApplicationLayer *gamelayer, ApplicationLayerType newLayerType)
{
    if(!gamelayer || newLayerType == GAME_LAYER) return;
}

void GameLayer_suspend(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return;
}

bool GameLayer_pollKeyInput(ApplicationLayer *gamelayer, InputContext inputContext) 
{
    if(!gamelayer) return false;

    if(InputContext_getKeyAction(inputContext, KEY_W) == KEY_PRESS)
    {
        Camera_moveForward(GAMELAYER_MAIN_CAMERA);
    }

    if(InputContext_getKeyAction(inputContext, KEY_S) == KEY_PRESS)
    {
        Camera_moveBackward(GAMELAYER_MAIN_CAMERA);
    }

    if(InputContext_getKeyAction(inputContext, KEY_A) == KEY_PRESS)
    {
        Camera_moveLeft(GAMELAYER_MAIN_CAMERA);
    }

    if(InputContext_getKeyAction(inputContext, KEY_D) == KEY_PRESS)
    {
        Camera_moveRight(GAMELAYER_MAIN_CAMERA);
    }

    if(InputContext_getKeyAction(inputContext, KEY_SPACE) == KEY_PRESS)
    {
        Camera_moveUp(GAMELAYER_MAIN_CAMERA);
    }

    if(InputContext_getKeyAction(inputContext, KEY_LEFT_SHIFT) == KEY_PRESS)
    {
        Camera_moveDown(GAMELAYER_MAIN_CAMERA);
    }


    return false;
}



bool GameLayer_onKeyInput(ApplicationLayer *gamelayer, KeyInputEvent event)
{
    if(!gamelayer) return false;

    switch(event.key)
    {   
        //Toggle Captured Cursor
        case KEY_ESC:
            if((event.action != KEY_PRESS)) break;
            if(InputContext_getMouseInputMode(event.context) == MOUSE_NORMAL) 
                InputContext_setMouseInputMode(event.context, MOUSE_HIDDEN_AND_CAPTURED);
            else
                InputContext_setMouseInputMode(event.context, MOUSE_NORMAL);
            break;
        default:
            return false;
    }

    return true;
}

bool GameLayer_onMouseMove(ApplicationLayer *gamelayer, MouseMoveEvent event)
{
    if(!gamelayer) return false;

    if(InputContext_getMouseInputMode(event.context) == MOUSE_HIDDEN_AND_CAPTURED)
        Camera_rotateOnCursorMove(GAMELAYER_MAIN_CAMERA, event.xPos, event.yPos);

    return false;
}

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

void GameLayer_setMainCamera(Camera* camera)
{
    GAMELAYER_MAIN_CAMERA = camera;
}
