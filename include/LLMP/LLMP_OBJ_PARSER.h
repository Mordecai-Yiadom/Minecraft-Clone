#ifndef LLMP_OBJ_PARSER_H
#define LLMP_OBJ_PARSER_H

#include "LLMP_TEXT_PARSER.h"

#define LLMP_DEFAULT_UV_COORD 0.0f
#define LLMP_DEFAULT_VERTEX_NORMAL 0.0f

#define OBJ_GROUP_DELIMITER "g "
#define OBJ_GROUP_DELIMITER_LEN 2

#define OBJ_FACE_DELIMITER "f "
#define OBJ_FACE_DELIMITER_LEN 2

#define OBJ_VERTEX_POSITION_DELIMITER "v "
#define OBJ_VETEX_POSITION_DELIMITER_LEN 2

#define OBJ_UV_COORD_DELIMITER "vt "
#define OBJ_UV_COORD_DELIMITER_LEN 3

#define OBJ_VERTEX_NORMAL_DELIMITER "vn "
#define OBJ_VERTEX_NORMAL_DELIMITER_LEN 3

typedef struct LLMP_OBJFileTempData
{
    LLMP_TextFileBuffer* textFileBuffer;
    size_t vertexCount;

    float *vertexBuffer;
    size_t vertexBufferLen;

    float *uvCoordBuffer;
    size_t uvCoordBufferLen;

    float *vertexNormalBuffer;
    size_t vertexNormalBufferLen;

    size_t groupCount;
}LLMP_OBJFileTempData;


LLMP_Model* LLMP_parseOBJModel(char *objFile);

static LLMP_OBJFileTempData* LLMP_OBJFileTempData_create(char *objFilePath);
static void LLMP_OBJFileTempData_free(LLMP_OBJFileTempData *buffer);

static size_t LLMP_OBJFileTempData_parseVertexCount(LLMP_OBJFileTempData* buffer);
static size_t LLMP_OBJFileTempData_parseUVCoordCount(LLMP_OBJFileTempData* buffer);
static size_t LLMP_OBJFileTempData_parseVertexNormalCount(LLMP_OBJFileTempData* buffer);
static size_t LLMP_OBJFileTempData_parseGroupCount(LLMP_OBJFileTempData* buffer);

static void LLMP_parseOBJGroupFace(LLMP_OBJFileTempData* buffer, LLMP_TextFileLine *lineToParse, LLMP_Mesh *mesh);
static bool LLMP_OBJFileTempData_parseVertexBuffer(LLMP_OBJFileTempData* buffer);
static bool LLMP_OBJFileTempData_parseUVCoordsBuffer(LLMP_OBJFileTempData* buffer);
static bool LLMP_OBJFileTempData_parseVertexNormalBuffer(LLMP_OBJFileTempData* buffer);


//TODO: Implement Edge-Case Error handling
LLMP_Model* LLMP_parseOBJModel(char *objFile)
{   
    if(!objFile) return NULL;

    LLMP_OBJFileTempData *tempData = LLMP_OBJFileTempData_create(objFile);
    if(!tempData) return NULL;

    //Init Model
    LLMP_Model *model = LLMP_CREATE_NULL_MODEL(1);
    LLMP_Mesh *currMesh = NULL;
    
    //Parse Model Meshes
    LLMP_TextFileLine *currLine = tempData->textFileBuffer->firstLine;
    
    while(currLine)
    {   
        if(LLMP_TextFileLine_startsWith(currLine, OBJ_GROUP_DELIMITER, OBJ_GROUP_DELIMITER_LEN) 
        ||LLMP_TextFileLine_startsWith(currLine, "o ", 2))
        {   
            //TODO add a create mesh function
            //Create next Mesh
            if(currMesh)
            {   
                currMesh->buffer = realloc(currMesh->buffer, currMesh->bufferLength * sizeof(float));
                currMesh->indexBuffer = realloc(currMesh->indexBuffer, currMesh->indexBufferLength * sizeof(unsigned int));

                currMesh->next = (LLMP_Mesh*) calloc(1, sizeof(LLMP_Mesh));
                currMesh = currMesh->next;
            }
            else 
            {
                currMesh = (LLMP_Mesh*) calloc(1, sizeof(LLMP_Mesh));
                model->meshes = currMesh;
            }
            
            //Create new current mesh
            currMesh->buffer = (float*) calloc((tempData->vertexBufferLen + tempData->uvCoordBufferLen + tempData->vertexNormalBufferLen) * 8, sizeof(float));
            currMesh->indexBuffer = (int*) calloc((tempData->vertexBufferLen + tempData->uvCoordBufferLen + tempData->vertexNormalBufferLen) * 8, sizeof(int));
            model->meshCount++;
        }   
        else if(LLMP_TextFileLine_startsWith(currLine, OBJ_FACE_DELIMITER, OBJ_FACE_DELIMITER_LEN) && currMesh)
        {   
            LLMP_parseOBJGroupFace(tempData, currLine, currMesh);
        }
        currLine = currLine->next;
    }
    LLMP_OBJFileTempData_free(tempData);
    return model;
}

static LLMP_OBJFileTempData* LLMP_OBJFileTempData_create(char *objFilePath)
{
    LLMP_OBJFileTempData *objFileBuffer = (LLMP_OBJFileTempData*) calloc(1, sizeof(LLMP_OBJFileTempData));  
    if(!objFileBuffer) return NULL;

    LLMP_TextFileBuffer* fileBuffer = LLMP_TextFileBuffer_create(objFilePath);
    if(!fileBuffer) return NULL;

    objFileBuffer->textFileBuffer = fileBuffer;

    //Parse Vertex Positions
    if(!LLMP_OBJFileTempData_parseVertexBuffer(objFileBuffer))
    {
        LLMP_OBJFileTempData_free(objFileBuffer);
        return NULL;
    }

    
    //Parse Texture Coords
    if(!LLMP_OBJFileTempData_parseUVCoordsBuffer(objFileBuffer))
    {
        LLMP_OBJFileTempData_free(objFileBuffer);
        return NULL;
    }
    
    //Parse Vertex Normals
    if(!LLMP_OBJFileTempData_parseVertexNormalBuffer(objFileBuffer))
    {
        LLMP_OBJFileTempData_free(objFileBuffer);
        return NULL;
    }

    return objFileBuffer;
}

static void LLMP_OBJFileTempData_free(LLMP_OBJFileTempData *buffer)
{
    if(!buffer) return;

    LLMP_TextFileBuffer_free(buffer->textFileBuffer);
    free(buffer->vertexBuffer);
    free(buffer->uvCoordBuffer);
    free(buffer->vertexNormalBuffer);

    free(buffer);
}

static size_t LLMP_OBJFileTempData_parseVertexCount(LLMP_OBJFileTempData* buffer)
{
    if(!buffer) return 0;
    
    LLMP_TextFileLine *currLine = buffer->textFileBuffer->firstLine;
    size_t vertexCount = 0;

    while(currLine)
    {   
        if(LLMP_TextFileLine_startsWith(currLine, OBJ_VERTEX_POSITION_DELIMITER, OBJ_VETEX_POSITION_DELIMITER_LEN)) 
            ++vertexCount;
        currLine = currLine->next;
    }

    return vertexCount;
}

static size_t LLMP_OBJFileTempData_parseGroupCount(LLMP_OBJFileTempData* buffer)
{
    if(!buffer) return 0;
    
    LLMP_TextFileLine *currLine = buffer->textFileBuffer->firstLine;
    size_t groupCount = 0;

    while(currLine)
    {   
        if(LLMP_TextFileLine_startsWith(currLine, "g ", 2)) ++groupCount;
        currLine = currLine->next;
    }

    return groupCount;
}

static size_t LLMP_OBJFileTempData_parseUVCoordCount(LLMP_OBJFileTempData* buffer)
{
    if(!buffer) return 0;
    
    LLMP_TextFileLine *currLine = buffer->textFileBuffer->firstLine;
    size_t uvCoordCount = 0;

    while(currLine)
    {   
        if(LLMP_TextFileLine_startsWith(currLine, OBJ_UV_COORD_DELIMITER, OBJ_UV_COORD_DELIMITER_LEN)) 
            ++uvCoordCount;
        currLine = currLine->next;
    }

    return uvCoordCount;
}

static size_t LLMP_OBJFileTempData_parseVertexNormalCount(LLMP_OBJFileTempData* buffer)
{
    if(!buffer) return 0;
    
    LLMP_TextFileLine *currLine = buffer->textFileBuffer->firstLine;
    size_t normalCount = 0;

    while(currLine)
    {   
        if(LLMP_TextFileLine_startsWith(currLine, OBJ_VERTEX_NORMAL_DELIMITER, OBJ_VERTEX_NORMAL_DELIMITER_LEN)) 
            ++normalCount;
        currLine = currLine->next;
    }
    return normalCount;
}



//CURRENTLY DOESN'T SUPPORT ANY MISSING INDEXES
static void LLMP_parseOBJGroupFace(LLMP_OBJFileTempData* objTempData, LLMP_TextFileLine *lineToParse, LLMP_Mesh *mesh)
{
    #define POS_STRIDE 3
    #define NORM_STRIDE 3
    #define UV_STRIDE 2

    if(!objTempData || !lineToParse || !mesh) return;

    size_t meshIndex = 0;
    // v/vt/vn indcies
    
    bool isQuad = (LLMP_countCharOccurrences(lineToParse->buffer, lineToParse->length, '/') == 8);
    char *token = strtok(lineToParse->buffer, " ");
    int currVPosIndex, currVTIndex, currVNIndex;

    while(token)
    {   
        if(token[0] == 'f') token = strtok(NULL, " ");
        
        if(strstr(token, "//")) 
        {
            sscanf(token, "%d//%d", &currVPosIndex, &currVNIndex);
            currVTIndex = 1;
        }
        else sscanf(token, "%d/%d/%d", &currVPosIndex, &currVTIndex, &currVNIndex);
        
        
        //Buffer Verts
        mesh->buffer[mesh->bufferLength++] = objTempData->vertexBuffer[(--currVPosIndex) * POS_STRIDE];
        mesh->buffer[mesh->bufferLength++] = objTempData->vertexBuffer[(currVPosIndex * POS_STRIDE) + 1];
        mesh->buffer[mesh->bufferLength++] = objTempData->vertexBuffer[(currVPosIndex * POS_STRIDE) + 2];

        mesh->buffer[mesh->bufferLength++] = objTempData->uvCoordBuffer[(--currVTIndex) * UV_STRIDE];
        mesh->buffer[mesh->bufferLength++] = objTempData->uvCoordBuffer[(currVTIndex * UV_STRIDE) + 1];

        mesh->buffer[mesh->bufferLength++] = objTempData->vertexNormalBuffer[(--currVNIndex) * NORM_STRIDE];
        mesh->buffer[mesh->bufferLength++] = objTempData->vertexNormalBuffer[(currVNIndex * NORM_STRIDE) + 1];
        mesh->buffer[mesh->bufferLength++] = objTempData->vertexNormalBuffer[(currVNIndex * NORM_STRIDE) + 2];
        
        //Buffer Indicies
        mesh->indexBuffer[mesh->indexBufferLength] = mesh->indexBufferLength;
        mesh->indexBufferLength++;
        
        //printf("%s\n", token);
        token = strtok(NULL, " ");
    }

    //Buffer Indecies
    if(isQuad)
    {
        mesh->indexBuffer[mesh->indexBufferLength] = mesh->indexBuffer[mesh->indexBufferLength-3];
        mesh->indexBufferLength++;
        mesh->indexBuffer[mesh->indexBufferLength] = mesh->indexBuffer[mesh->indexBufferLength-3];
        mesh->indexBufferLength++;
    }
}

static bool LLMP_OBJFileTempData_parseVertexBuffer(LLMP_OBJFileTempData* tempData)
{   
    static float tempBuff[3];

    if(!tempData || !tempData->textFileBuffer) return false;
    
    size_t vertexCount = LLMP_OBJFileTempData_parseVertexCount(tempData);
    float *buffer = calloc(vertexCount * 3, sizeof(float));

    LLMP_TextFileLine *currLine = tempData->textFileBuffer->firstLine;
    int buffIndex = 0;
  
    while(currLine)
    {   
        if(LLMP_TextFileLine_startsWith(currLine, "v ", 2))
        {
            sscanf(currLine->buffer, "v %f %f %f", &tempBuff[0], &tempBuff[1], &tempBuff[2]);

            buffer[buffIndex++] = tempBuff[0];
            buffer[buffIndex++] = tempBuff[1];
            buffer[buffIndex++] = tempBuff[2];            
        }
        currLine = currLine->next;
    }

    
    tempData->vertexBufferLen = vertexCount * 3;
    tempData->vertexBuffer = buffer;

    return true;
}

static bool LLMP_OBJFileTempData_parseUVCoordsBuffer(LLMP_OBJFileTempData* tempData)
{   
    static float tempBuff[2];

    if(!tempData || !tempData->textFileBuffer) return false;
    
    size_t uvCoordCount = LLMP_OBJFileTempData_parseUVCoordCount(tempData);
    float *buffer = calloc(uvCoordCount * 2, sizeof(float));
    
    LLMP_TextFileLine *currLine = tempData->textFileBuffer->firstLine;
    int buffIndex = 0;
    
    while(currLine)
    {   
        if(LLMP_TextFileLine_startsWith(currLine, "vt ", 3))
        {
            sscanf(currLine->buffer, "vt %f %f", &tempBuff[0], &tempBuff[1]);

            buffer[buffIndex++] = tempBuff[0];
            buffer[buffIndex++] = tempBuff[1];       
        }
        currLine = currLine->next;
    }
    tempData->uvCoordBufferLen = uvCoordCount * 2;
    tempData->uvCoordBuffer = buffer;
    return true;
}

static bool LLMP_OBJFileTempData_parseVertexNormalBuffer(LLMP_OBJFileTempData* tempData)
{   
    static float tempBuff[3];

    if(!tempData || !tempData->textFileBuffer) return false;
    
    size_t normalCount = LLMP_OBJFileTempData_parseVertexNormalCount(tempData);
    float *buffer = calloc(normalCount * 3, sizeof(float));
    
    LLMP_TextFileLine *currLine = tempData->textFileBuffer->firstLine;
    int buffIndex = 0;

    while(currLine)
    {   
        if(LLMP_TextFileLine_startsWith(currLine, "vn ", 3))
        {
            sscanf(currLine->buffer, "vn %f %f %f", &tempBuff[0], &tempBuff[1], &tempBuff[2]);

            buffer[buffIndex++] = tempBuff[0];
            buffer[buffIndex++] = tempBuff[1];
            buffer[buffIndex++] = tempBuff[2];
        }

        currLine = currLine->next;
    }

    tempData->vertexNormalBufferLen = normalCount * 3;
    tempData->vertexNormalBuffer = buffer;
    return true;
}


#endif