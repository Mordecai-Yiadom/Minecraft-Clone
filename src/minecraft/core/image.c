#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stdbool.h>

Image Image_create(const char* path, bool flipVertically)
{
    if(!path) return IMAGE_NULL;
    Image image;
    stbi_set_flip_vertically_on_load(flipVertically);
    
    image.pixels = stbi_load(path, &image.width, &image.height, &image.channelCount, 0);
    return image;
}

void Image_destroy(Image *image)
{
    if(!image) return;
    free(image);
}

bool Image_isValid(Image *image)
{
    if(!image) return false;
    return (bool) (image->pixels) 
    && image->height > 0 
    && image->width > 0 
    && image->channelCount > 0 ;
}