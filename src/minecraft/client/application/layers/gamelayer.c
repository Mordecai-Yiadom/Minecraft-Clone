#include "gamelayer.h"

#include "../../system.render/backend/backend.h"
#include "../../system.render/rendersystem.h"
#include "../../system.render/renderer.h"

#include "../application.h"

static Camera camera;

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
    return gamelayer;
}

void GameLayer_destroy(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return;
}

void GameLayer_onRender(ApplicationLayer *gamelayer)
{   
    static bool isInitialized = false;
    //static Quad quad1;
    static Transform3D quad1Transform;
    static Shader shader;
    
    
    if(!gamelayer) return;

    if(!isInitialized)
    {   
        shader = Shader_create("assets/minecraft/shaders/default.vs", NULL, "assets/minecraft/shaders/default.fs");
        if(!Shader_isValid(shader)) Logger_logError(RENDER_SYSTEM, "Shader Program handle is invalid.");

        memset(&quad1Transform, 0, sizeof(Transform3D));
        Quad_create(quad1Transform);
        
        PerspCameraProjectionData projData;
        projData.fov = 90;
        projData.aspectRatio = 1280.0f/720.0f;
        camera = Camera_createPerspective(projData, 0.1, 1000);
        
        isInitialized = true;
    }

    Renderer_setClearColor((Color){.red=0.1, 0.2, 0.4, 1});
    Renderer_clearBuffer(COLOR_BUFFER);
    
    Shader_enable(shader);
    Shader_setFloat(shader, "r", sin(glfwGetTime()));
    Shader_setFloat(shader, "g", cos(glfwGetTime()));
    Shader_setFloat(shader, "b", sin(glfwGetTime()) * cos(glfwGetTime()));

    //Camera_setFov(&camera, 100 * sin(glfwGetTime()));

    vec3 camera_position = {0, 0, 0};
    vec3f(quad1Transform.position, 0, 0, 5);

    glm_mat4_identity(quad1Transform.matrix);
    glm_translate(quad1Transform.matrix, quad1Transform.position);

    Camera_setPosition(&camera, camera_position);
    camera.direction[2] = 10 * sin(glfwGetTime());
    Camera_updateMatrix(&camera);
    
    Shader_setMat4x4f(shader, "projection", camera.matrix.projection);
    Shader_setMat4x4f(shader, "view", camera.matrix.view);
    Shader_setMat4x4f(shader, "model", quad1Transform.matrix);

    
    Quad_draw();

    //printf("[FPS] %d\n", RenderSystem_fps());
     
}

void GameLayer_onUpdate(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return;
    puts("GameLayer OnUpdate");
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
