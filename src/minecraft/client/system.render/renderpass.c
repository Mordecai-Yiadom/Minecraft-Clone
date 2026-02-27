#include "renderpass.h"

#define COMMAND_QUEUE_SIZE 1000

RenderPass RenderPass_create(RenderPipeline pipeline, RenderTarget renderTarget)
{
    RenderPass renderPass;
    renderPass.commandQueue = Queue_create(COMMAND_QUEUE_SIZE, sizeof(RenderCommand), STATIC_MEMORY);
    renderPass.pipeline = pipeline;
    renderPass.renderTarget = renderTarget;
    return renderPass;
}

void RenderPass_submitCommand(RenderPass *renderPass, RenderCommand command)
{
    if(!renderPass) return;
    Queue_enqueue(&renderPass->commandQueue, (byte*)&command);
}

void RenderPass_execute(RenderPass *renderPass)
{   
    if(!renderPass) return;
    int length = Queue_length(&renderPass->commandQueue);
    RenderCommand currCommand;
    for(int i = 0; i < length; i++)
    {   
        Queue_peek(&renderPass->commandQueue, (byte*)&currCommand);
        RenderCommand_execute(currCommand);
        Queue_dequeue(&renderPass->commandQueue);
    }
}

void RenderPass_destroy(RenderPass *renderPass)
{
    if(!renderPass) return;
    Queue_destroy(&renderPass->commandQueue);
    RenderPipeline_destroy(&renderPass->pipeline);
    RenderTarget_destroy(&renderPass->renderTarget);
}
