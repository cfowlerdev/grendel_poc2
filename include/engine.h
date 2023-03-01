#pragma once
#include <string>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>

class Engine {
public:
    Engine(const std::string &p_title, const int &p_width, const int &p_height);
    ~Engine();
    
    GLFWwindow *windowId;
    int width;
    int height;
private:
    
};
