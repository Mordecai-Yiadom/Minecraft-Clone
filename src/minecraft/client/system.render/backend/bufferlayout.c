#include "bufferlayout.h"

#include <stdarg.h>

BufferLayout BufferLayout_create(BufferLayoutPattern layoutPattern, int attributeCount, ...)
{
    BufferLayout bufferLayout = {.layoutPattern=layoutPattern};

    va_list attributes;
    va_start(attributes, attributeCount);

    for(int i = 0; i < attributeCount; i++)
    {
        BufferLayout_addAttribute(&bufferLayout, va_arg(attributes, BufferAttribute));
    }

    va_end(attributes);
    return bufferLayout;
}


void BufferLayout_addAttribute(BufferLayout *bufferLayout, BufferAttribute bufferAttribute)
{
    if(!bufferLayout || bufferAttribute.size < Primative_sizeof(BYTE)) return;
    if(bufferLayout->attributeCount == BUFFERLAYOUT_MAX_ATTRIBUTES) return;

    switch(bufferAttribute.type)
    {
        case VEC1_ATTRIBUTE:
        case VEC2_ATTRIBUTE:
        case VEC3_ATTRIBUTE:
        case VEC4_ATTRIBUTE:
            if(bufferAttribute.componentCount < 1 || bufferAttribute.componentCount > 4)
                return;
            break;

        case MAT2x2_ATTRIBUTE:
            BufferLayout_addAttribute(bufferLayout, aVEC2(bufferAttribute.componentType));
            BufferLayout_addAttribute(bufferLayout, aVEC2(bufferAttribute.componentType));
            return;

        case MAT3x3_ATTRIBUTE:
            BufferLayout_addAttribute(bufferLayout, aVEC3(bufferAttribute.componentType));
            BufferLayout_addAttribute(bufferLayout, aVEC3(bufferAttribute.componentType));
            BufferLayout_addAttribute(bufferLayout, aVEC3(bufferAttribute.componentType));
            return;

        case MAT4x4_ATTRIBUTE:
            BufferLayout_addAttribute(bufferLayout, aVEC4(bufferAttribute.componentType));
            BufferLayout_addAttribute(bufferLayout, aVEC4(bufferAttribute.componentType));
            BufferLayout_addAttribute(bufferLayout, aVEC4(bufferAttribute.componentType));
            BufferLayout_addAttribute(bufferLayout, aVEC4(bufferAttribute.componentType));            
            return;
    }

    switch(bufferLayout->layoutPattern)
    {
        case INTERLEAVED:
            bufferLayout->stride += bufferAttribute.size;
            bufferAttribute.offset = 0; 
            for(int i = 0; i < bufferLayout->attributeCount; i++)
            {
                bufferAttribute.offset += bufferLayout->attributes[i].size;
            }        
            break;

        case SEQUENTIAL:
            break;
    }
    
    bufferLayout->attributes[bufferLayout->attributeCount++] = bufferAttribute;
}
