#include "rendercommand.h"

void RenderCommand_execute(RenderCommand command)
{
    if(!command.address) return;
    command.address(command.args);
}

bool RenderCommand_isValid(RenderCommand command)
{
    return (command.address != NULL);
}