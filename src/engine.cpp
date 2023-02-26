#include <iostream>
#include <vector>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "opengl/camera.h"
#include "opengl/model.h"

#include "engine.h"
#include "entity.h"

void Engine::onUpdate()
{
}

void Engine::init(const std::string &p_title, const int &p_width, const int &p_height)
{
    std::cout << "- Engine init" << std::endl;
}