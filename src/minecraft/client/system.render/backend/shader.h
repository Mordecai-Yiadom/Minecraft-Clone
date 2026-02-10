#ifndef MINECRAFT_CLIENT_RENDER_SYSTEM_SHADER_H
#define MINECRAFT_CLIENT_RENDER_SYSTEM_SHADER_H

#include "../../../core/core.h"
#include "buffer.h"

#define SHADER_NULL ((Shader){.id=0})

#ifdef MINECRAFT_CLIENT_RENDER_SYSTEM_SHADER_C
    static GLuint complileIndividualShader(GLenum shaderType, const char* path);
#endif

typedef enum UniformBlockBindingPoint
{
    CAMERA_MATRIX,
    POINT_LIGHTS, //Remove Possibly
    AUX_SLOT_1,
    AUX_SLOT_2,
    AUX_SLOT_3,
    AUX_SLOT_4,
    AUX_SLOT_5,
    AUX_SLOT_6,
    AUX_SLOT_7,
}UniformBlockBindingPoint;

typedef struct Shader
{
    unsigned int id;
}Shader;

Shader Shader_create(const char* vertexShaderPath, const char* geometryShaderPath, const char* fragmentShaderPath);
void Shader_destroy(Shader shader);

void Shader_enable(Shader shader);
void Shader_disable();

bool Shader_isValid(Shader shader);

void Shader_setInt(Shader shader, const char* uniformName, int data);
void Shader_setUnsignedInt(Shader shader, const char* uniformName, unsigned int data);
void Shader_setFloat(Shader shader, const char* uniformName, float data);

void Shader_setVec2i(Shader shader, const char* uniformName, ivec2 data);
void Shader_setVec3i(Shader shader, const char* uniformName, ivec3 data);
void Shader_setVec4i(Shader shader, const char* uniformName, ivec4 data);

void Shader_setVec2f(Shader shader, const char* uniformName, vec2 data);
void Shader_setVec3f(Shader shader, const char* uniformName, vec3 data);
void Shader_setVec4f(Shader shader, const char* uniformName, vec4 data);

void Shader_setMat2x2f(Shader shader, const char* uniformName, mat2 data);
void Shader_setMat3x3f(Shader shader, const char* uniformName, mat3 data);
void Shader_setMat4x4f(Shader shader, const char* uniformName, mat4 data);

void Shader_linkUniformBuffer(Shader shader, UniformBuffer uniformBuffer, UniformBlockBindingPoint bindingPoint, const char* uniformName);


#endif