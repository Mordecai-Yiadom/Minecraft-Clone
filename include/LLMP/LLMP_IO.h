#ifndef LLMP_IO_H
#define LLMP_IO_H

#include "LLMP.h"

char* LLMP_read_file(char* filePath, size_t *length);


#ifndef LLMP_IO_IMPLEMENTED
#define LLMP_IO_IMPLEMENTED
char* LLMP_read_file(char* filePath, size_t *length)
{
    FILE *file = fopen(filePath, "r");
    if(!file) return NULL;

    fseek(file, 0, SEEK_END);
    long fileLen = ftell(file);

    if(fileLen == -1) return NULL;
    fseek(file, 0, SEEK_SET);
    
    char *fileBuffer = (char*) calloc(fileLen, sizeof(char));
    if(!fileBuffer) return NULL;

    fread(fileBuffer, sizeof(char), fileLen, file);
    fclose(file);

    if(length) *length = (size_t) fileLen;
    return fileBuffer;
}

#endif

#endif