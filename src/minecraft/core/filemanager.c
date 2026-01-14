#include "filemanager.h"
#include "core.h"

char* FileManager_readFile(const char* path, size_t* size)
{
    FILE *file = fopen(path, "r");
    if(size) *size = 0;
    if(!file) return NULL;

    fseek(file, 0, SEEK_END);
    long fileLen = ftell(file);

    if(fileLen == -1) return NULL;
    fseek(file, 0, SEEK_SET);
    
    char *fileSource = calloc(fileLen, sizeof(char));
    if(!fileSource) return NULL;

    fread(fileSource, sizeof(char), fileLen, file);
    fclose(file);

    if(size) *size = (size_t) fileLen;

    return fileSource;
}