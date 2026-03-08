#ifndef MINECRAFT_CLIENT_DRAWCOMMAND_H
#define MINECRAFT_CLIENT_DRAWCOMMAND_H

#include "../backend/mesh.h"

typedef struct DrawMeshIndexedCommandArgs
{
    Mesh *mesh;
}DrawMeshIndexedCommandArgs;

void DrawMeshIndexedCommand(void *args);

#endif