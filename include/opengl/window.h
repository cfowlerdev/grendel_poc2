#pragma once

#include <string>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window
{
public:
    Window(const std::string &p_title, const int &p_width, const int &p_height);
    ~Window();

    void clear();
    void update();

    GLFWwindow *windowId;

private:
    std::string _title;
    int _width;
    int _height;
    glm::vec4 _backgroundColor;

};
