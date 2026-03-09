#include "drawcommand.h"

void DrawMeshIndexedCommand(void *args)
{   
    if(!args) return;
    DrawMeshIndexedCommandArgs cmdArgs;
    cmdArgs.mesh = (Mesh*) args;
    

    if(!Mesh_isValid(cmdArgs.mesh)) return;
    
    int eboLength = IndexBuffer_length(&cmdArgs.mesh->ebo);
    if(eboLength > 0)
    {   
        VertexArray_bind(&cmdArgs.mesh->vao);
        glDrawElements(GL_TRIANGLES, eboLength, cmdArgs.mesh->ebo.type, NULL);
        VertexArray_unbind();
        
    }
}