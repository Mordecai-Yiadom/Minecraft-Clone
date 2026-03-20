#define MINECRAFT_CLIENT_GAME_BLOCKTEXTURE_C
#include "blocktexture.h"

#define MAX_BLOCK_TEXTURES 4

void BlockTexture_createAll()
{   
    
    BlockTexture_create(DIRT, "assets/minecraft/textures/blocks/dirt.png");
    BlockTexture_create(STONE, "assets/minecraft/textures/blocks/stone.png");
    BlockTexture_create(GRASS, "assets/minecraft/textures/blocks/null.png");
}


void BlockTexture_create(BlockType blockType, char *path)
{   
    if(!isManagerInitialized) BlockTextureManager_init();
    if(!path) return;

    Texture2D texture = Texture2D_create(path);
    printf("Block Texture [%d]: %d\n", BLOCKTEXTURE_MANAGER.textureCount, texture.samplerID);
    Array_insert(&BLOCKTEXTURE_MANAGER.textures, blockType, (byte*)&texture);
    BLOCKTEXTURE_MANAGER.textureCount++;
}


static inline void BlockTextureManager_init()
{   
    if(isManagerInitialized) return;
    BLOCKTEXTURE_MANAGER.textures = Array_create(MAX_BLOCK_TEXTURES, sizeof(Texture2D));

    isManagerInitialized = true;
}


void BlockTextureManager_writeTexturesToShader(Shader shader)
{   
    if(!isManagerInitialized || !Shader_isValid(shader)) return;

    BlockTextureManager_activateTextures();

    int data[MAX_BLOCK_TEXTURES];
    memset(&data, 0, sizeof(data));
    Texture2D currTexture;

    char uniformName[32];

    for(int i = 0; i < MAX_BLOCK_TEXTURES ; i++)
    {   
        if(i == AIR) continue;

        memset(&uniformName, 0, sizeof(uniformName));
        Array_get(&BLOCKTEXTURE_MANAGER.textures, i, (byte*)&currTexture);
        data[i] = currTexture.samplerID;

        sprintf(uniformName, "blockTextures[%d]", i);
        Shader_setInt(shader, uniformName, currTexture.samplerID);

        printf("%s: %d\n", uniformName, currTexture.samplerID);
    }    
}

static inline void BlockTextureManager_activateTextures()
{
    Texture2D currTexture;
    for(int i = 0; i < MAX_BLOCK_TEXTURES ; i++)
    {   
        if(i == AIR) continue;
        Array_get(&BLOCKTEXTURE_MANAGER.textures, i, (byte*)&currTexture);
        
        glActiveTexture(currTexture.samplerID + GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, currTexture.id);
    }    
}
