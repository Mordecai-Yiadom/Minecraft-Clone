#include "shader.h"

#define LOG_BUFFER_SIZE 512
#define CLEAR_LOG_BUFFER() memset(logBuffer, 0, LOG_BUFFER_SIZE)

//TODO: Enable individual shader reuse

static GLuint complileIndividualShader(GLenum shaderType, const char* path)
{   
    static char logBuffer[LOG_BUFFER_SIZE]; 
    CLEAR_LOG_BUFFER();

    char* shaderSrc = FileManager_readFile(path, NULL);
    if(!shaderSrc)
    {   
        sprintf(logBuffer, "Failed to read file '%s'.", path);
        Logger_logError(FILE_IO, logBuffer);
        return 0;
    }
     
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, (GLsizei) 1, (const GLchar**) &shaderSrc, NULL);
    glCompileShader(shader);

    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

    if(!compileStatus)
    {   
        glGetShaderInfoLog(shader, (GLsizei) LOG_BUFFER_SIZE, (GLsizei*) NULL, logBuffer);
        Logger_logError(RENDER_SYSTEM, logBuffer);
        free(shaderSrc);
        return 0;
    }
    
    free(shaderSrc);
    return shader;
}


Shader Shader_create(const char* vertexShaderPath, const char* geometryShaderPath, const char* fragmentShaderPath)
{
    if(!vertexShaderPath || !fragmentShaderPath)
    {
        fputs("Failed to create shader. Null vertex and/or fragment path(s).", stderr);
        return SHADER_NULL;
    }
    
    GLuint vertexShader = complileIndividualShader(GL_VERTEX_SHADER, vertexShaderPath);
    if(!glIsShader(vertexShader)) return SHADER_NULL;
   
    GLuint fragmentShader = complileIndividualShader(GL_FRAGMENT_SHADER, fragmentShaderPath);
    if(!glIsShader(fragmentShader))
    {   
        glDeleteShader(vertexShader);
        return SHADER_NULL;
    } 

    GLuint geometryShader = 0;
    if(geometryShaderPath) geometryShader = complileIndividualShader(GL_GEOMETRY_SHADER, geometryShaderPath);
    

    Shader shaderProgram = {.id=glCreateProgram()};

    glAttachShader((GLuint) shaderProgram.id, vertexShader);
    glAttachShader((GLuint) shaderProgram.id, fragmentShader);
    if(glIsShader(geometryShader)) glAttachShader((GLuint) shaderProgram.id, geometryShader);

    glLinkProgram((GLuint) shaderProgram.id);

    //Clean up
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(geometryShader);
    
    return shaderProgram;
}

void Shader_destroy(Shader shader)
{
    glDeleteProgram((GLuint) shader.id);
}

void Shader_enable(Shader shader)
{
    glUseProgram((GLuint) shader.id);
}
void Shader_disable()
{
    glUseProgram(0);
}

void Shader_setInt(Shader shader, const char* uniformName, int data)
{
    if(!uniformName || !shader.id) return;
    glUniform1i(glGetUniformLocation((GLuint) shader.id, (const GLchar*) uniformName), (GLint) data);
}

void Shader_setUnsignedInt(Shader shader, const char* uniformName, unsigned int data)
{
    if(!uniformName || !shader.id) return;
    glUniform1ui(glGetUniformLocation((GLuint) shader.id, (const GLchar*) uniformName), (GLuint) data);
}

void Shader_setFloat(Shader shader, const char* uniformName, float data)
{
    if(!uniformName || !shader.id) return;
    glUniform1f(glGetUniformLocation((GLuint) shader.id, (const GLchar*) uniformName), (GLfloat) data);
}

void Shader_setVec2i(Shader shader, const char* uniformName, ivec2 data)
{
    if(!uniformName || !shader.id) return;
    glUniform2iv(glGetUniformLocation((GLuint) shader.id, (const GLchar*) uniformName), 1, (const GLint*) &data);
}

void Shader_setVec3i(Shader shader, const char* uniformName, ivec3 data)
{
    if(!uniformName || !shader.id) return;
    glUniform3iv(glGetUniformLocation((GLuint) shader.id, (const GLchar*) uniformName), 1, (const GLint*) &data);
}

void Shader_setVec4i(Shader shader, const char* uniformName, ivec4 data)
{
    if(!uniformName || !shader.id) return;
    glUniform4iv(glGetUniformLocation((GLuint) shader.id, (const GLchar*) uniformName), 1, (const GLint*) &data);
}

void Shader_setVec2f(Shader shader, const char* uniformName, vec2 data)
{
    if(!uniformName || !shader.id) return;
    glUniform2fv(glGetUniformLocation((GLuint) shader.id, (const GLchar*) uniformName), 1, (const GLfloat*) &data);
}

void Shader_setVec3f(Shader shader, const char* uniformName, vec3 data)
{
    if(!uniformName || !shader.id) return;
    glUniform3fv(glGetUniformLocation((GLuint) shader.id, (const GLchar*) uniformName), 1, (const GLfloat*) &data);
}

void Shader_setVec4f(Shader shader, const char* uniformName, vec4 data)
{
    if(!uniformName || !shader.id) return;
    glUniform4fv(glGetUniformLocation((GLuint) shader.id, (const GLchar*) uniformName), 1, (const GLfloat*) &data);
}

void Shader_setMat2x2f(Shader shader, const char* uniformName, mat2 data)
{
    if(!uniformName || !shader.id) return;
    glUniformMatrix2fv(glGetUniformLocation((GLuint) shader.id, (const GLchar*) uniformName), 1, GL_FALSE, (const GLfloat*) &data);
}

void Shader_setMat3x3f(Shader shader, const char* uniformName, mat3 data)
{
    if(!uniformName || !shader.id) return;
    glUniformMatrix3fv(glGetUniformLocation((GLuint) shader.id, (const GLchar*) uniformName), 1, GL_FALSE, (const GLfloat*) &data);
}

void Shader_setMat4x4f(Shader shader, const char* uniformName, mat4 data)
{
    if(!uniformName || !shader.id) return;
    glUniformMatrix4fv(glGetUniformLocation((GLuint) shader.id, (const GLchar*) uniformName), 1, GL_FALSE, (const GLfloat*) &data);
}

void Shader_linkUniformBuffer(Shader shader, UniformBuffer uniformBuffer, UniformBlockBindingPoint bindingPoint, const char* uniformName)
{
    if(!uniformName || !shader.id) return;
    glUniformBlockBinding((GLuint) shader.id, (GLuint) glGetUniformBlockIndex((GLuint) shader.id, (const GLchar*) uniformName), (GLuint) bindingPoint);
    glBindBufferBase(GL_UNIFORM_BUFFER, (GLuint) bindingPoint, (GLuint) uniformBuffer.id);
}