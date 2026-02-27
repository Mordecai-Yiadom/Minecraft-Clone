#ifndef MINECRAFT_CLIENT_DRAWCOMMAND_H
#define MINECRAFT_CLIENT_DRAWCOMMAND_H

#include "../backend/mesh.h"

typedef void(*DrawMeshIndexedCommandAddress)(Mesh *mesh);

typedef struct DrawMeshIndexedCommandArgs
{
    Mesh *mesh;
}DrawMeshIndexedCommandArgs;

typedef struct DrawMeshIndexedCommand
{
    DrawMeshIndexedCommandAddress cmdAddress;
    DrawMeshIndexedCommandArgs args;
}DrawMeshIndexedCommand;



#endif