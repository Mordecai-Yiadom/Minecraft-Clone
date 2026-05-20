#ifndef MINECRAFT_CLIENT_RENDERPASS_H
#define MINECRAFT_CLIENT_RENDERPASS_H


#include "backend/backend.h"

#include "rendercommand.h"
#include "renderpipeline.h"
#include "rendertarget.h"

#define COMMAND_TAG_LEN 16

#define CHUNKRENDERPASS_INDEX 0


typedef struct RenderPass
{   
    char tag[COMMAND_TAG_LEN];
    ArrayList commandBuffer;
    RenderPipeline pipeline;
    RenderTarget renderTarget;
    RenderState renderstate;
}RenderPass;

RenderPass RenderPass_create(char* tag, RenderPipeline pipeline, RenderTarget renderTarget);

void RenderPass_submitCommand(RenderPass *renderPass, RenderCommand command);

void RenderPass_execute(RenderPass *renderPass);

void RenderPass_destory(RenderPass *renderPass);

#endif