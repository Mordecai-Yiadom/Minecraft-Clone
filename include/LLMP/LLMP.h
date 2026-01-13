#ifndef LLMP_H
#define LLMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LLMP_CREATE_NULL_MODEL(modelCount) (LLMP_Model*) calloc(modelCount, sizeof(LLMP_Model))

typedef struct LLMP_Mesh
{
    float *buffer;
    size_t bufferLength;

    int *indexBuffer;
    size_t indexBufferLength;

    struct LLMP_Mesh *next;
}LLMP_Mesh;


typedef struct LLMP_Model
{
    LLMP_Mesh *meshes;
    unsigned int meshCount;
}LLMP_Model;

typedef enum LLMP_SupportedFileType
{
    OBJ,
}LLMP_SupportedFileType;

void *LLMP_Model_free(LLMP_Model *model);
static void LLMP_Mesh_free(LLMP_Mesh* mesh);

#ifdef LLMP_ENABLE_ASSERTIONS
    void ASSERT_MODEL_INFO(LLMP_Model *model)
    {
        if(!model) puts("Model is null.");
        else printf("Mesh Count: %d\n", model->meshCount);
        int meshCount = 0;
        LLMP_Mesh *currMesh = model->meshes;

        while(currMesh)
        {   
            printf("Mesh %d: bufferLen=%ld, indexBufferLen=%ld\n", meshCount++, currMesh->bufferLength, currMesh->indexBufferLength);
            currMesh = currMesh->next;
        }
    }

    #define LLMP_ASSERT(msg) puts(msg);
    #define LLMP_ASSERT_RAN() LLMP_ASSERT("Success.")

#else
    void ASSERT_MODEL_INFO(LLMP_Model *model)
    {}
#endif



#endif