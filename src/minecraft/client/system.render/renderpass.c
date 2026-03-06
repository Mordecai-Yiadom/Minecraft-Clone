#include "renderpass.h"

#define COMMAND_QUEUE_SIZE 4
static int commandsSumbitted = 0;
RenderPass RenderPass_create(char* tag, RenderPipeline pipeline, RenderTarget renderTarget)
{
    RenderPass renderPass;
    if(tag) memcpy(&renderPass.tag, tag, COMMAND_TAG_LEN);
    renderPass.commandBuffer = ArrayList_create(COMMAND_QUEUE_SIZE, sizeof(RenderCommand), DYNAMIC_MEMORY);
    renderPass.pipeline = pipeline;
    renderPass.renderTarget = renderTarget;
    return renderPass;
}

void RenderPass_submitCommand(RenderPass *renderPass, RenderCommand command)
{   
    if(!renderPass || !RenderCommand_isValid(command)) return;
    ArrayList_add(&renderPass->commandBuffer, (byte*)&command);
    commandsSumbitted++;
    puts("Command Submitted");
}

void RenderPass_execute(RenderPass *renderPass)
{   
    static int passCount = 0;
    if(!renderPass) return;
    int length = ArrayList_length(&renderPass->commandBuffer);
    printf("Commands Submitted: %d\n", commandsSumbitted);
    if(length <= 0)
    {
        puts("Invalid Queue length");
        return;
    }
    
    RenderCommand currCommand;
    memset(&currCommand, 0, sizeof(RenderCommand));

    for(int i = 0; i < commandsSumbitted; i++)
    {   
        printf("I: %d\n", i);
        
        ArrayList_get(&renderPass->commandBuffer, i, (byte*)&currCommand);
        RenderCommand_execute(currCommand);
    }
    puts("[RenderPass] pass completed");
    ArrayList_clear(&renderPass->commandBuffer);

    //if(passCount == 4) exit(0);
    passCount++;
    commandsSumbitted = 0;
}

void RenderPass_destroy(RenderPass *renderPass)
{
    if(!renderPass) return;
    ArrayList_destroy(&renderPass->commandBuffer);
    // RenderPipeline_destroy(&renderPass->pipeline);
    // RenderTarget_destroy(&renderPass->renderTarget);
}
