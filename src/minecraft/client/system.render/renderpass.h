#ifndef MINECRAFT_CLIENT_RENDERPASS_H
#define MINECRAFT_CLIENT_RENDERPASS_H

#include "../../core/queue.h"
#include "backend/backend.h"

#include "rendercommand.h"
#include "renderpipeline.h"
#include "rendertarget.h"

#define COMMAND_TAG_LEN 16

typedef struct RenderPass
{   
    char tag[COMMAND_TAG_LEN];
    ArrayList commandBuffer;
    RenderPipeline pipeline;
    RenderTarget renderTarget;
}RenderPass;

RenderPass RenderPass_create(char* tag, RenderPipeline pipeline, RenderTarget renderTarget);

void RenderPass_submitCommand(RenderPass *renderPass, RenderCommand command);

void RenderPass_execute(RenderPass *renderPass);

void RenderPass_destory(RenderPass *renderPass);

#endif