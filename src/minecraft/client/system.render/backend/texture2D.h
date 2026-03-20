#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_TEXTURE2D_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_TEXTURE2D_H

#include "backend.h"


typedef struct Texture2D
{   
    Image image;
    unsigned int id;
    unsigned int samplerID;
}Texture2D;

Texture2D Texture2D_create(char *imagePath);
void Texture2D_destroy(Texture2D *texture);

#ifdef MINECRAFT_CLIENT_RENDER_SYSTEM_TEXTURE2D_C
static int TEXTURE2D_NEXT_TEXTURE_UNIT = GL_TEXTURE0;
#endif

#endif