#define MINECRAFT_CLIENT_RENDER_SYSTEM_QUAD_C
#include "quad.h"

#include "../renderer.h"

static bool quadMeshInitialized = false;
static inline void Quad_init()
{   
    BufferData vertexData = {.buffer=QUAD_VERTEX_DATA, .size=sizeof(QUAD_VERTEX_DATA)};
    BufferData indexData = {.buffer=QUAD_INDEX_DATA, .size=sizeof(QUAD_INDEX_DATA)};

    MeshData meshData;
    meshData.format = POS3f_NORM3f_UV2f;
    meshData.vertexData = vertexData;
    meshData.indexData = indexData;
    meshData.type = STATIC;

    QUAD_MESH = Mesh_create(meshData);
    
    quadMeshInitialized = true;
    puts("Quad Mesh Initialized");
}


Quad Quad_create(Transform3D transform)
{
    if(!quadMeshInitialized)
    {   
        puts("Quad Mesh not valid");
        Quad_init();
    } 

    Quad quad = {.transform=transform};
    return quad;
}

void Quad_draw()
{    
    puts("Draw Quad Command Requested");
    if(quadMeshInitialized)
    {   
        Renderer_drawMesh(&QUAD_MESH);
        // puts("Quad Draw Command Submited");
    } 
}