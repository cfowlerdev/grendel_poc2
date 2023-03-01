#pragma once
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaders/program.h"
#include "mesh.h"

class Model
{
public:
    Model(const std::string& p_filename, const std::string& p_directory);

    void draw(Program& p_program);

    GLint vertexCount;
    GLint trisCount;

    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> texures_loaded;

private:
    Texture loadMaterialTexture(const std::string& p_path, const std::string& p_typeName);
};
