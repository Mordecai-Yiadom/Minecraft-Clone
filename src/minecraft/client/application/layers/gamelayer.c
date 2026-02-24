#include "gamelayer.h"

#include "../../system.render/backend/backend.h"
#include "../../system.render/rendersystem.h"



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
    static VertexBuffer vbo;
    static VertexArray vao;
    static Shader shader;
    static Camera camera;

    static float shapeVerts[] = 
    {   
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  0,0,-1,     
        0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  0,0,-1,     
        0.5f, 0.5f, -0.5f,    1.0f, 1.0f, 0,0,-1,     
        0.5f, 0.5f, -0.5f,     1.0f, 1.0f, 0,0,-1,     
        -0.5f, 0.5f, -0.5f,    0.0f, 1.0f,  0,0,-1,     
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,   0,0,-1,    

    };
    
    if(!gamelayer) return;

    if(!isInitialized)
    {   
        
        BufferData data = {.buffer=&shapeVerts, .size=sizeof(shapeVerts)};
        printf("data.buffer=%p\n", data.buffer);
        printf("data.size=%lld\n", data.size);
        
        BufferLayout vbolayout = BufferLayout_create(INTERLEAVED, 3, aVEC3(FLOAT), aVEC3(FLOAT), aVEC2(FLOAT));

        vbo = VertexBuffer_create(data, STATIC_DRAW, vbolayout);
        if(!VertexBuffer_isValid(&vbo)) Logger_logError(RENDER_SYSTEM, "VBO handle is invalid.");
        
        printf("VBO handle: %d\n", vbo.id);
        printf("VBO size: %d\n",  VertexBuffer_getSize(&vbo));
        
        vao = VertexArray_create(INDEXBUFFER_NULL, 1, vbo);
        VertexArray_addVertexBuffer(&vao, vbo);
        
        shader = Shader_create("assets/shaders/default.vs", NULL, "assets/shaders/default.fs");

        if(!VertexArray_isValid(&vao)) Logger_logError(RENDER_SYSTEM, "VAO handle is invalid.");
        if(!Shader_isValid(shader)) Logger_logError(RENDER_SYSTEM, "Shader Program handle is invalid.");

        PerspCameraProjectionData projData;
        projData.fov = 90;
        projData.aspectRatio = 1280.0f/720.0f;
        camera = Camera_createPerspective(projData, 0.1, 1000);
        
        isInitialized = true;
    }

    glClearColor(0,0,0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    Shader_enable(shader);
    VertexArray_bind(&vao);
    
    Shader_setFloat(shader, "r", sin(glfwGetTime()));
    Shader_setFloat(shader, "g", cos(glfwGetTime()));
    Shader_setFloat(shader, "b", tan(glfwGetTime()));

    //Camera_setFov(&camera, 100 * sin(glfwGetTime()));

    vec3 camera_position = {0, 0, 0};
    
    mat4 modelMatrix;
    
    vec3 modelPos = {0, 0, 5};
    
    glm_mat4_identity(modelMatrix);
    glm_translate(modelMatrix, modelPos);

    Camera_setPosition(&camera, camera_position);
    camera.direction[2] = 10 * sin(glfwGetTime());
    Camera_updateMatrix(&camera);
    
   

    Shader_setMat4x4f(shader, "projection", camera.matrix.projection);
    Shader_setMat4x4f(shader, "view", camera.matrix.view);
    Shader_setMat4x4f(shader, "model", modelMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    
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
    return true;
}

bool GameLayer_onMouseInput(ApplicationLayer *gamelayer)
{
    if(!gamelayer) return false;
    return true;
}
