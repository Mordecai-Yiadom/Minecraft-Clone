#ifndef MINECRAFT_CLIENT_RENDERPIPELINE_H
#define MINECRAFT_CLIENT_RENDERPIPELINE_H

#include "backend/backend.h"
#include "renderer.h"
#include "rendertarget.h"

typedef struct RenderPipeline RenderPipeline;

typedef void(*RenderPipelineLoad)(RenderPipeline *pipeline, RenderTarget *renderTarget);
typedef void (*RenderPipelineUnload)(RenderPipeline *pipeline, RenderTarget *renderTarget);

typedef struct RenderPipeline
{
    Shader shader;
    RenderPipelineLoad loadProc;
    RenderPipelineUnload unloadProc;
    bool isLoaded;
}RenderPipeline;

RenderPipeline RenderPipeline_create(Shader shader, RenderPipelineLoad loadProc, RenderPipelineUnload unloadProc);

void RenderPipeline_destroy(RenderPipeline* pipeline, RenderTarget *renderTarget);

void RenderPipeline_load(RenderPipeline *pipeline, RenderTarget *target);

void RenderPipeline_unload(RenderPipeline *pipeline, RenderTarget *target);

bool RenderPipeline_isValid(RenderPipeline *pipeline);

#endif