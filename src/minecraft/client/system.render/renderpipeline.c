#include "renderpipeline.h"

RenderPipeline RenderPipeline_create(Shader shader, RenderPipelineLoad loadProc, RenderPipelineUnload unloadProc)
{
    RenderPipeline pipeline;
    pipeline.shader = shader;
    pipeline.loadProc = loadProc;
    pipeline.unloadProc = unloadProc;
    pipeline.isLoaded = false;
    return pipeline;
}

void RenderPipeline_destroy(RenderPipeline* pipeline, RenderTarget *renderTarget)
{
    if(!pipeline) return;
    if(pipeline->isLoaded) RenderPipeline_unload(pipeline, renderTarget);
}

void RenderPipeline_load(RenderPipeline *pipeline, RenderTarget *renderTarget)
{
    if(!RenderPipeline_isValid(pipeline)) return;
    if(pipeline->loadProc) 
    {   
        Shader_enable(pipeline->shader);
        pipeline->loadProc(pipeline, renderTarget);
    }
    
    pipeline->isLoaded = true;
}

void RenderPipeline_unload(RenderPipeline *pipeline, RenderTarget *renderTarget)
{
    if(!RenderPipeline_isValid(pipeline)) return;
    if(pipeline->unloadProc)
    {   
        Shader_disable();
        pipeline->unloadProc(pipeline, renderTarget);
    } 
    pipeline->isLoaded = false;
}

bool RenderPipeline_isValid(RenderPipeline *pipeline)
{
    if(!pipeline) return false;
    return (Shader_isValid(pipeline->shader) && (pipeline->loadProc != NULL) && (pipeline->unloadProc != NULL));
}
