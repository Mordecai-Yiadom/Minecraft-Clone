#ifndef MINECRAFT_CLIENT_RENDERPASS_H
#define MINECRAFT_CLIENT_RENDERPASS_H

#include "../../core/queue.h"
#include "backend/backend.h"

#include "rendercommand.h"
#include "renderpipeline.h"
#include "rendertarget.h"



typedef struct RenderPass
{   
    Queue commandQueue;
    RenderPipeline pipeline;
    RenderTarget renderTarget;
}RenderPass;

RenderPass RenderPass_create(RenderPipeline pipeline, RenderTarget renderTarget);

void RenderPass_submitCommand(RenderPass *renderPass, RenderCommand command);

void RenderPass_execute(RenderPass *renderPass);

void RenderPass_destory(RenderPass *renderPass);

#endif