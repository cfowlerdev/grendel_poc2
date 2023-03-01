#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaders/shader.h"

class Program 
{
public:
    Program(std::vector<Shader *> shaders);
    Program(const std::string& p_vertexShader, const std::string& p_fragmentShader);
    ~Program();

    GLuint programId;
    static Program *currentProgram;

    GLuint bind();
    GLuint unbind();

    GLuint getAttrib(const GLchar *attribName);
    GLuint getUniform(const GLchar *uniformName);

    void setBool(const std::string& p_name, bool value) const;
    void setInt(const std::string& p_name, int value) const;
    void setFloat(const std::string& p_name, float value) const;
    void setVec2(const std::string& p_name, const glm::vec2& value) const;
    void setVec2(const std::string& p_name, float x, float y) const;
    void setVec3(const std::string& p_name, const glm::vec3& value) const;
    void setVec3(const std::string& p_name, float x, float y, float z) const;
    void setVec4(const std::string& p_name, const glm::vec4& value) const;
    void setVec4(const std::string& p_name, float x, float y, float z, float w) const;
    void setMat2(const std::string& p_name, const glm::mat2& value) const;
    void setMat3(const std::string& p_name, const glm::mat3& value) const;
    void setMat4(const std::string& p_name, const glm::mat4& value) const;

private:
    int _linkShaders();
};
