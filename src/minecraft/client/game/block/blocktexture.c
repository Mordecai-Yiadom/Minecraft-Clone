#define MINECRAFT_CLIENT_GAME_BLOCKTEXTURE_C
#include "blocktexture.h"

#define MAX_BLOCK_TEXTURES 10

void BlockTexture_createAll()
{   
    BlockTexture_create(GRASS, "assets/minecraft/textures/blocks/grass.png");
    BlockTexture_create(STONE, "assets/minecraft/textures/blocks/stone.png");
    BlockTexture_create(DIRT, "assets/minecraft/textures/blocks/dirt.png");
    BlockTexture_create(BEDROCK, "assets/minecraft/textures/blocks/bedrock.png");
    BlockTexture_create(DIAMOND_ORE, "assets/minecraft/textures/blocks/diamond_ore.png");
    BlockTexture_create(UNKNOWN, "assets/minecraft/textures/blocks/null.png");
}


void BlockTexture_create(BlockType blockType, char *path)
{   
    if(!isManagerInitialized) BlockTextureManager_init();
    if(!path) return;

    Texture2D texture = Texture2D_create(path);
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

    for(BlockType i = AIR; i < MAX_BLOCK_TEXTURES ; i++)
    {   
        memset(uniformName, 0, sizeof(uniformName));
        Array_get(&BLOCKTEXTURE_MANAGER.textures, i, (byte*)&currTexture);
        data[i] = currTexture.samplerID;

        sprintf(uniformName, "blockTextures[%d]", i);
        Shader_setInt(shader, uniformName, currTexture.samplerID);
    }    
}

static inline void BlockTextureManager_activateTextures()
{
    Texture2D currTexture;
    for(int i = 0; i < MAX_BLOCK_TEXTURES ; i++)
    {   
        Array_get(&BLOCKTEXTURE_MANAGER.textures, i, (byte*)&currTexture);
        if(Texture2D_isValid(&currTexture)) Texture2D_activate(&currTexture);
    }    
}
