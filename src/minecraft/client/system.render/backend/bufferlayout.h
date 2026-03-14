#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_BUFFERLAYOUT_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_BUFFERLAYOUT_H

#include "context.h"
#include "primatives.h"
#include "../../../core/core.h"

#define BUFFERLAYOUT_MAX_ATTRIBUTES 16

typedef struct BufferData
{
    size_t size;
    void* buffer;
}BufferData;

typedef struct IndexBufferData
{
    size_t size;
    void* buffer;
    Primative elementType;
}IndexBufferData;


typedef enum BufferAttributeType
{   
    VEC1_ATTRIBUTE,
    VEC2_ATTRIBUTE,
    VEC3_ATTRIBUTE,
    VEC4_ATTRIBUTE,

    MAT2x2_ATTRIBUTE,
    MAT3x3_ATTRIBUTE,
    MAT4x4_ATTRIBUTE,

}BufferAttributeType;

typedef struct BufferAttribute
{   
    BufferAttributeType type;
    size_t offset;
    int size;

    int componentCount;
    int attributeDivisor;
    Primative componentType;
    GLboolean isNormalized;
    
}BufferAttribute;

typedef enum BufferLayoutPattern
{
    INTERLEAVED,
    SEQUENTIAL
}BufferLayoutPattern;

typedef struct BufferLayout
{
    BufferAttribute attributes[BUFFERLAYOUT_MAX_ATTRIBUTES];
    int stride;
    int attributeCount;
    BufferLayoutPattern layoutPattern;
}BufferLayout;



#define aVEC1(t) ((BufferAttribute){.componentType=t, .componentCount=1, .isNormalized=false, .size=Primative_sizeof(t), .type=VEC1_ATTRIBUTE}, .offset=0)
#define aVEC2(t) ((BufferAttribute){.componentType=t, .componentCount=2, .isNormalized=false, .size=Primative_sizeof(t) * 2, .type=VEC2_ATTRIBUTE, .offset=0})
#define aVEC3(t) ((BufferAttribute){.componentType=t, .componentCount=3, .isNormalized=false, .size=Primative_sizeof(t) * 3, .type=VEC3_ATTRIBUTE, .offset=0})
#define aVEC4(t) ((BufferAttribute){.componentType=t, .componentCount=4, .isNormalized=false, .size=Primative_sizeof(t) * 4, .type=VEC4_ATTRIBUTE, .offset=0})

#define aMAT2x2(t) ((BufferAttribute){.componentType=t, .isNormalized=false, .size=(Primative_sizeof(t) * 2) * 2, .type=MAT2x2_ATTRIBUTE, .offset=0})
#define aMAT3x3(t) ((BufferAttribute){.componentType=t, .isNormalized=false, .size=(Primative_sizeof(t) * 3) * 3, .type=MAT3x3_ATTRIBUTE, .offset=0})
#define aMAT4x4(t) ((BufferAttribute){.componentType=t, .isNormalized=false, .size=(Primative_sizeof(t) * 4) * 4, .type=MAT4x4_ATTRIBUTE, .offset=0})

#define aUBYTE() aVEC1(UNSIGNED_BYTE)
#define aBYTE() aVEC1(BYTE)

#define aUSHORT aVEC1(UNSIGNED_SHORT)
#define aSHORT() aVEC1(SHORT)

#define aUINT() aVEC1(UNSIGNED_INT)
#define aINT() aVEC1(INT)

#define aFLOAT() aVEC1(FLOAT)
#define aDOUBLE() aVEC1(DOUBLE)

BufferLayout BufferLayout_create(BufferLayoutPattern layoutPattern, int attributeCount, ...);

void BufferLayout_addAttribute(BufferLayout *bufferLayout, BufferAttribute bufferAttribute);




#endif