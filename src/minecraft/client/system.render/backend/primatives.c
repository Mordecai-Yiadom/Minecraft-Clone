#include "primatives.h"

int Primative_sizeof(Primative primative)
{
    switch(primative)
    {   
        case BYTE:
        case UNSIGNED_BYTE:
            return sizeof(GLbyte);

        case SHORT:
        case UNSIGNED_SHORT:
            return sizeof(GLshort);

        case INT:
        case UNSIGNED_INT:
            return sizeof(GLint);
        
        case FLOAT:
            return sizeof(GLfloat);

        case DOUBLE:
            return sizeof(GLdouble);
    }

    return 0;
}