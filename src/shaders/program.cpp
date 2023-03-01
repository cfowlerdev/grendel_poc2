#include <iostream>
#include "shaders/program.h"

Program *Program::currentProgram = nullptr;


Program::Program(std::vector<Shader *> shaders)
{
    programId = glCreateProgram();

    for(std::vector<Shader *>::iterator shader = shaders.begin(); shader != shaders.end(); shader++)
    {
        glAttachShader(programId, (*shader)->shaderId);
    }

    _linkShaders();

    // No longer need for the shaders code as they've been linked into the program
    for(std::vector<Shader *>::iterator shader = shaders.begin(); shader != shaders.end(); shader++)
    {
        glDetachShader(programId, (*shader)->shaderId);
        glDeleteShader((*shader)->shaderId);
    }
}

Program::Program(const std::string& p_vertexShader, const std::string& p_fragmentShader)
{
    programId = glCreateProgram();

    // Vertex shader
    Shader vertexShader = Shader(p_vertexShader, GL_VERTEX_SHADER);
    glAttachShader(programId, vertexShader.shaderId);
    Shader fragmentShader = Shader(p_fragmentShader, GL_FRAGMENT_SHADER);
    glAttachShader(programId, fragmentShader.shaderId);

    _linkShaders();

    glDetachShader(programId, vertexShader.shaderId);
    glDeleteShader(vertexShader.shaderId);
    glDetachShader(programId, fragmentShader.shaderId);
    glDeleteShader(fragmentShader.shaderId);
}

int Program::_linkShaders()
{
    glLinkProgram(programId);

    GLint status;
    glGetProgramiv(programId, GL_LINK_STATUS, &status);
    if(status != GL_TRUE)
    {
        GLint logLen;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLen);
        GLchar *log = new GLchar[logLen + 1];
        glGetProgramInfoLog(programId, logLen + 1, nullptr, log);
        std::cout << "ERROR : Unable to link program : " << std::to_string(programId) << " - " << std::string(log) << std::endl;
        return -1;
    }
    return 1;
}

Program::~Program()
{
    glDeleteProgram(programId);
}

GLuint Program::bind()
{
    currentProgram = this;
    glUseProgram(programId);
    return programId;
}

GLuint Program::unbind()
{
    currentProgram = nullptr;
    glUseProgram(0);
    return 0;
}

GLuint Program::getAttrib(const GLchar *attribName)
{
    return glGetAttribLocation(programId, attribName);
}

GLuint Program::getUniform(const GLchar *uniformName)
{
    return glGetUniformLocation(programId, uniformName);
}


void Program::setBool(const std::string& p_name, bool value) const
{
    glUniform1i(glGetUniformLocation(programId, p_name.c_str()), (int)value);     
}

void Program::setInt(const std::string& p_name, int value) const
{
    glUniform1i(glGetUniformLocation(programId, p_name.c_str()), value); 
}

void Program::setFloat(const std::string& p_name, float value) const
{
    glUniform1f(glGetUniformLocation(programId, p_name.c_str()), value);
}

void Program::setVec2(const std::string& p_name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(programId, p_name.c_str()), 1, &value[0]);
}

void Program::setVec2(const std::string& p_name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(programId, p_name.c_str()), x, y); 
}

void Program::setVec3(const std::string& p_name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(programId, p_name.c_str()), 1, &value[0]); 
}

void Program::setVec3(const std::string& p_name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(programId, p_name.c_str()), x, y, z); 
}

void Program::setVec4(const std::string& p_name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(programId, p_name.c_str()), 1, &value[0]); 
}

void Program::setVec4(const std::string& p_name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(programId, p_name.c_str()), x, y, z, w); 
}

void Program::setMat2(const std::string& p_name, const glm::mat2& value) const
{
    glUniformMatrix2fv(glGetUniformLocation(programId, p_name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Program::setMat3(const std::string& p_name, const glm::mat3& value) const
{
    glUniformMatrix3fv(glGetUniformLocation(programId, p_name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Program::setMat4(const std::string& p_name, const glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(programId, p_name.c_str()), 1, GL_FALSE, &value[0][0]);
}

