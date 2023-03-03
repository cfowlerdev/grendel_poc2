#include <iostream>
#include "engine.h"

static void windowPosCallback(GLFWwindow* window, int x, int y)
{
    std::cout << ">>> windowPosCallback(" << x << ", " << y << ")" << std::endl;
}

static void windowSizeCallback(GLFWwindow* window, int width, int height)
{
    std::cout << ">>> windowSizeCallback(" << width << ", " << height << ")" << std::endl;
}

static void windowMaximizeCallback(GLFWwindow* window, int maximized)
{
    if(maximized)
    {
        std::cout << ">>> windowMaximizeCallback : MAXIMIZED" << std::endl;    
    }
    else
    {
        std::cout << ">>> windowMaximizeCallback : UN-MAXIMIZED" << std::endl;
    }
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    std::cout << ">>> mouseButtonCallback(" << button << ", " << action << ", " << mods << ")" << std::endl;
}

static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    std::cout << ">>> cursorPosCallback(" << xpos << ", " << ypos << ")"  << std::endl;
}

static void cursorEnterCallback(GLFWwindow* window, int entered)
{
    if(entered)
    {
        std::cout << ">>> Mouse entered <<<" << std::endl;
    } else {
        std::cout << ">>> Mouse left <<<" << std::endl;
    }
}

static void scrollCallback(GLFWwindow* window, double x, double y)
{
    std::cout << ">>> scrollCallback(" << x << ", " << y << ")" << std::endl;
}

static void charCallback(GLFWwindow* window, unsigned int codepoint)
{
    std::cout << ">>> charCallback(" << codepoint << ")" << std::endl;
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    std::cout << ">>> keyCallback(" << key << ", " << scancode << ", " << action << " , " << mods << ")" << std::endl;
}

static void dropCallback(GLFWwindow* window, int count, const char** paths)
{
    std::cout << ">>> dropCallback(" << count << ")" << std::endl;
}

static void errorCallback(int error, const char* description)
{
    std::cout << "GLFW ERROR(" << error << ": " << description << std::endl;
}

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

    // Callbacks
	glfwSetWindowPosCallback(windowId, windowPosCallback);
	glfwSetWindowSizeCallback(windowId, windowSizeCallback);
	// glfwSetWindowMaximizeCallback(windowId, windowMaximizeCallback);
	glfwSetMouseButtonCallback(windowId, mouseButtonCallback);
	glfwSetCursorPosCallback(windowId, cursorPosCallback);
	glfwSetCursorEnterCallback(windowId, cursorEnterCallback);
	glfwSetScrollCallback(windowId, scrollCallback);
	glfwSetCharCallback(windowId, charCallback);
	glfwSetKeyCallback(windowId, keyCallback);
	glfwSetDropCallback(windowId, dropCallback);

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // Initialize the master renderer
    m_Camera = new Camera();
    m_Renderer = new Renderer();
}

Engine::~Engine()
{
    glfwTerminate();
}

void Engine::render()
{
    m_Renderer->render(*m_Camera);
}
