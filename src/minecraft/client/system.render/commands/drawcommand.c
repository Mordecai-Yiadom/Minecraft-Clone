#include "drawcommand.h"

void DrawMeshIndexedCommand(void *args)
{   
    if(!args) return;
    DrawMeshIndexedCommandArgs *cmdArgs = (DrawMeshIndexedCommandArgs*) args;
    Mesh *mesh = (Mesh*) cmdArgs->mesh;
    
    if(!Mesh_isValid(mesh))
    {   
        return;
    }
    
    int eboLength = IndexBuffer_length(&mesh->ebo);
    if(eboLength > 0)
    {   
        //mesh->ebo.type
        VertexArray_bind(&mesh->vao);
        glDrawElements(GL_TRIANGLES, eboLength, UNSIGNED_INT, NULL);
        VertexArray_unbind();
        
    }
}