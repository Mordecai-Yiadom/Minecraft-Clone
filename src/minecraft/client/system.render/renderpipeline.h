#ifndef MINECRAFT_CLIENT_RENDERPIPELINE_H
#define MINECRAFT_CLIENT_RENDERPIPELINE_H

#include "backend/backend.h"

typedef void(*RenderPipelineLoad)();
typedef void (*RenderPipelineUnload)();

typedef struct RenderPipeline
{
    Shader shader;
    RenderPipelineLoad loadProc;
    RenderPipelineUnload unloadProc;
}RenderPipeline;

RenderPipeline RenderPipeline_create(Shader shader);

void RenderPipeline_destroy(RenderPipeline* pipeline);

#endif