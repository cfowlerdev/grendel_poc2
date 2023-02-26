#include <iostream>
#include "opengl/window.h"

Window::Window(const std::string &p_title, const int &p_width, const int &p_height)
    : _title(p_title), _width(p_width), _height(p_height), _backgroundColor(glm::vec4(0, 0, 0, 1))
{
    windowId = glfwCreateWindow(p_width, p_height, p_title.c_str(), NULL, NULL);

    if(!windowId)
    {
        std::cout << "ERROR : Unable to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(windowId);

    // TODO
    // glfwSetWindowSizeCallback(windowId, resizeCallback);

    clear();
}

Window::~Window()
{
    glfwDestroyWindow(windowId);
}

void Window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(_backgroundColor.x, _backgroundColor.y, _backgroundColor.z, _backgroundColor.w);
}

void Window::update()
{
    glfwPollEvents();
    glfwSwapBuffers(windowId);
}
