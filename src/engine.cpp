#include <iostream>
#include "engine.h"

Engine::Engine(const std::string &p_title, const int &p_width, const int &p_height)
    : width(p_width), height(p_height)
{
    // Init GLFW
    // TODO: detect version
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);    

    // Create window
    windowId = glfwCreateWindow(p_width, p_height, p_title.c_str(), NULL, NULL);
    
    if(!windowId)
    {
        std::cout << "ERROR : Unable to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(windowId);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // TODO: Set callbacks
    // glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    // glfwSetCursorPosCallback(window, mouseCallback);
    // glfwSetScrollCallback(window, scrollCallback);
    
    // capture mouse
    glfwSetInputMode(windowId, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

}

Engine::~Engine()
{
    glfwTerminate();
}
