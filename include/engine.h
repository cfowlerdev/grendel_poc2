#pragma once
#include <string>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "objects/camera.h"
#include "renderers/renderer.h"

class Engine {
public:
    Engine(const std::string &p_title, const int &p_width, const int &p_height);
    ~Engine();

    void render();

    GLFWwindow *windowId;
    int width;
    int height;
private:
    Camera *m_Camera;
    Renderer *m_Renderer;
};
