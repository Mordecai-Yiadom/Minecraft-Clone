#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_PRIMATIVES_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_PRIMATIVES_H

#include "context.h"
typedef enum Primative
{
    BYTE = GL_BYTE,
    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,

    SHORT = GL_SHORT,
    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,

    INT = GL_INT,
    UNSIGNED_INT = GL_UNSIGNED_INT,

    FLOAT = GL_FLOAT,
    DOUBLE = GL_DOUBLE,
}Primative;

int Primative_sizeof(Primative primative);
#endif