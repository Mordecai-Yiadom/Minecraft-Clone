
#define MINECRAFT_CLIENT_RENDER_SYSTEM_TEXTURE2D_C
#include "texture2D.h"
#include <string.h>

#define Texture2D_isSamplerValid(id) (id > 0 && id < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)

Texture2D Texture2D_create(char *imagePath)
{   
    Texture2D texture;
    memset(&texture, 0, sizeof(Texture2D));

    if(!imagePath) return texture;

    texture.image = Image_create(imagePath, true);
    if(!Image_isValid(&texture.image)) return texture;

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    if(!glIsTexture(texture.id)) return texture;

    GLint internalFormat;
    GLenum format;
    
    switch(texture.image.channelCount)
    {   
        case 1:
            internalFormat = GL_RGBA8;
            format = GL_RGB;
            break;
        case 3:
            internalFormat = GL_RGB;
            format = GL_RGB;
            break;
        case 4:
            internalFormat = GL_RGBA;
            format = GL_RGBA;
            break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, 
        internalFormat, 
        texture.image.width, 
        texture.image.height, 
        0, 
        format, 
        GL_UNSIGNED_BYTE, 
        texture.image.pixels);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //Set Active Texture
    if(Texture2D_isSamplerValid(TEXTURE2D_NEXT_TEXTURE_UNIT))
    {
        glActiveTexture(TEXTURE2D_NEXT_TEXTURE_UNIT);
        glBindTexture(GL_TEXTURE_2D, texture.id);
        texture.samplerID = (TEXTURE2D_NEXT_TEXTURE_UNIT - GL_TEXTURE0);
        TEXTURE2D_NEXT_TEXTURE_UNIT++;
    }

    return texture;
}

void Texture2D_activate(Texture2D *texture)
{
    if(!texture) return;
    glActiveTexture(texture->samplerID + GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->id);
}

bool Texture2D_isValid(Texture2D *texture)
{
    if(!texture) return false;
    return (glIsTexture(texture->id) && Texture2D_isSamplerValid(texture->samplerID));
} 