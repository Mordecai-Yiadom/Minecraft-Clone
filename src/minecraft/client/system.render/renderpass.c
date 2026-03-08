#include "renderpass.h"

#define COMMAND_QUEUE_SIZE 4
static int commandsSumbitted = 0;
RenderPass RenderPass_create(char* tag, RenderPipeline pipeline, RenderTarget renderTarget)
{
    RenderPass renderPass;
    if(tag) memcpy(&renderPass.tag, tag, COMMAND_TAG_LEN);
    renderPass.commandBuffer = ArrayList_create(COMMAND_QUEUE_SIZE, sizeof(RenderCommand), STATIC_MEMORY);
    renderPass.pipeline = pipeline;
    renderPass.renderTarget = renderTarget;
    return renderPass;
}

void RenderPass_submitCommand(RenderPass *renderPass, RenderCommand command)
{   
    if(!renderPass || !RenderCommand_isValid(command)) return;
    ArrayList_add(&renderPass->commandBuffer, (byte*)&command);
    commandsSumbitted++;
}

void RenderPass_execute(RenderPass *renderPass)
{   
    if(!renderPass) return;
    int length = ArrayList_length(&renderPass->commandBuffer);
    if(length <= 0) return;
    
    RenderPipeline_load(&renderPass->pipeline, &renderPass->renderTarget);

    RenderCommand currCommand;
    memset(&currCommand, 0, sizeof(RenderCommand));

    for(int i = 0; i < commandsSumbitted; i++)
    {        
        ArrayList_get(&renderPass->commandBuffer, i, (byte*)&currCommand);
        RenderCommand_execute(currCommand);
    }

    ArrayList_clear(&renderPass->commandBuffer);

    RenderPipeline_unload(&renderPass->pipeline, &renderPass->renderTarget);

    commandsSumbitted = 0;
}

void RenderPass_destroy(RenderPass *renderPass)
{
    if(!renderPass) return;
    ArrayList_destroy(&renderPass->commandBuffer);
    RenderPipeline_destroy(&renderPass->pipeline, &renderPass->renderTarget);
    // RenderTarget_destroy(&renderPass->renderTarget);
}
