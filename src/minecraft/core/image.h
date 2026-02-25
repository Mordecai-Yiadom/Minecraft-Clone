#ifndef MINECRAFT_CORE_IMAGE_H
#define MINECRAFT_CORE_IMAGE_H

#include "memtypes.h"
#include <stdbool.h>
#define IMAGE_NULL ((Image){.pixels=0, .width=0, .height=0, .channelCount=0})

typedef struct Image
{   
    u8* pixels;
    i32 width;
    i32 height;
    i32 channelCount;
}Image;

Image Image_create(const char* path, bool flipVertically);

void Image_destroy(Image *image);

bool Image_isValid(Image *image);

#endif