#ifndef MINECRAFT_CLIENT_GAME_BLOCKTEXTURE_H
#define MINECRAFT_CLIENT_GAME_BLOCKTEXTURE_H

#include "../../system.render/backend/backend.h"
#include "../../../core/game/block/block.h"
#include "../../../core/core.h"


typedef struct BlockTextureManager
{
    Array textures;
    int textureCount;
}BlockTextureManager;

#ifdef MINECRAFT_CLIENT_GAME_BLOCKTEXTURE_C
    static BlockTextureManager BLOCKTEXTURE_MANAGER;
    static bool isManagerInitialized = false;
    static inline void BlockTextureManager_init();
    static inline void BlockTextureManager_activateTextures();
#endif

void BlockTexture_createAll();

void BlockTexture_create(BlockType blockType, char *path);

void BlockTextureManager_writeTexturesToShader(Shader shader);




#endif