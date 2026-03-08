#include "chunkrenderpass.h"
#include "../pipelines/genericpipeline.h"
RenderPass ChunkRenderPass_create()
{   
    
    //Create RenderTarget
    RenderTarget renderTarget;
    PerspCameraProjectionData projData;
    projData.fov = 90;
    projData.aspectRatio = 1280.0f/720.0f;
    renderTarget.camera = Camera_createPerspective(projData, 0.1, 1000);
    
    RenderPass renderPass = RenderPass_create("Chunk-Pass", GenericPipeline_create(), renderTarget);

    return renderPass;
}