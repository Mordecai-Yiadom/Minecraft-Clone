#ifndef LLMP_TEXT_PARSER_H
#define LLMP_TEXT_PARSER_H

#include "LLMP.h"
#include "LLMP_IO.h"

typedef struct LLMP_TextFileLine
{   
    char *buffer;
    size_t length;

    struct LLMP_TextFileLine *next;
}LLMP_TextFileLine;

typedef struct LLMP_TextFileBuffer
{
    LLMP_TextFileLine *firstLine;
    LLMP_TextFileLine *lastLine;
}LLMP_TextFileBuffer;



LLMP_TextFileBuffer* LLMP_TextFileBuffer_create(char *filePath);
void LLMP_TextFileBuffer_free(LLMP_TextFileBuffer* buffer);

static void LLMP_TextFileLine_free(LLMP_TextFileLine* buffer);


LLMP_TextFileLine* LLMP_TextFileBuffer_getLine(LLMP_TextFileBuffer* buffer, int lineNum);
size_t LLMP_TextFileBuffer_lineCount(LLMP_TextFileBuffer *buffer);

bool LLMP_TextFileLine_startsWith(LLMP_TextFileLine *line, char *pattern, size_t patternLen);
int LLMP_countCharOccurrences(char *str, size_t strLen, char symbol);

#define isVecfChar(c) (c >= '0' && c <= '9') || (c == '+' || c == '-' || c == '.')
float* LLMP_parseVecf(char *text, size_t textLen, int vecLen);


//Implementations
int LLMP_countCharOccurrences(char *str, size_t strLen, char symbol)
{
    if(!str) return 0;
    int count = 0;

    for(size_t i = 0; i < strLen; ++i) if(str[i] == symbol) ++count;

    return count;
}

//BROKEN FUNCTION: MUST FIX NOW
float* LLMP_parseVecf(char *text, size_t textLen, int vecLen)
{
    if(vecLen < 1) return NULL;
    float *parsedVec = calloc(vecLen, sizeof(float));
    size_t vecIndex = 0;
    for(size_t i = 0; i < textLen; i++)
    {   
        if(text[i] == ' ') 
        {
            parsedVec[vecIndex++] = strtof(&text[i], (char**)NULL);
            if(vecIndex == vecLen) break;
        }
    }

    return parsedVec;
}

LLMP_TextFileBuffer* LLMP_TextFileBuffer_create(char *filePath)
{
    size_t fileLen;
    char *fileBuffer = LLMP_read_file(filePath, &fileLen);
    if(!fileBuffer) return NULL;

    LLMP_TextFileBuffer *textFileBuffer = calloc(1, sizeof(LLMP_TextFileBuffer));
    LLMP_TextFileLine *currentLine = calloc(1, sizeof(LLMP_TextFileLine));
    textFileBuffer->firstLine = currentLine;
    currentLine->buffer = &fileBuffer[0];
    size_t currrentLineLength = 0;

    for(size_t i = 0; i < fileLen; i++)
    {   
        if(fileBuffer[i] == 0)
        {
            textFileBuffer->lastLine = currentLine;
            break;
        }
        else if(fileBuffer[i] == '\n')
        {   
            fileBuffer[i] = 0;
            currentLine->next = calloc(1, sizeof(LLMP_TextFileLine));
            currentLine = (LLMP_TextFileLine *) currentLine->next;
            currentLine->buffer = &fileBuffer[i+1];
        }
        currentLine->length++; 
    }
    
    return textFileBuffer;
}
void LLMP_TextFileBuffer_free(LLMP_TextFileBuffer* buffer)
{}

static void LLMP_TextFileLine_free(LLMP_TextFileLine* buffer)
{}


LLMP_TextFileLine* LLMP_TextFileBuffer_getLine(LLMP_TextFileBuffer* buffer, int lineNum)
{
    if(!buffer || lineNum < 1) return NULL;

    LLMP_TextFileLine *currFileLine = buffer->firstLine;
    size_t currLineNum = 0;

    while(currFileLine)
    {
        ++currLineNum;
        currFileLine = currFileLine->next;
        if(currLineNum == lineNum) return currFileLine; 
    }

    return NULL;
}


size_t LLMP_TextFileBuffer_lineCount(LLMP_TextFileBuffer *buffer)
{   
    if(!buffer) return 0;

    LLMP_TextFileLine *currLine = buffer->firstLine;
    size_t lineCount = 0;
    while(currLine)
    {
        ++lineCount;
        currLine = currLine->next;
    }

    return lineCount;
}

bool LLMP_TextFileLine_startsWith(LLMP_TextFileLine *line, char *pattern, size_t patternLen)
{
    if(!line || !pattern || patternLen == 0) return false;
    if(line->length < patternLen) return false;
    
    for(size_t i = 0; i < patternLen; ++i) 
        if(line->buffer[i] != pattern[i]) return false;
    return true;
}



#endif