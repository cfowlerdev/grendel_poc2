#include <iostream>
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "opengl/program.h"
#include "opengl/camera.h"

#include "entity.h"


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define NUM_ENTITIES 10000


Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

float zoom = 45.0f;
float movementSpeed = 2.5f;
float mouseSensitivity = 0.1f;

GLFWwindow* window;
Program *program;
Entity *entity;

std::vector<Entity *> entities;

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    // camera.ProcessMouseScroll(static_cast<float>(yoffset));
    float floatYoffset = static_cast<float>(yoffset);
    zoom -= (float) floatYoffset;
    if(zoom < 1.0f)
        zoom = 1.0f;
    if(zoom > 45.0f)
        zoom = 45.0f;
}

void processInput(GLFWwindow *window)
{
    // if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    //     glfwSetWindowShouldClose(window, true);
    float velocity = movementSpeed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.position += camera.front * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.position -= camera.front * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.position -= camera.right * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.position += camera.right * velocity;
}

// ===========================================
// EMSCRIPTEN MAIN LOOP
// ===========================================
void main_loop()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;    

    // INPUT
    processInput(window);

    // RENDER
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     

    // bind textures on corresponding texture units
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, texture1);
    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, texture2);

    // activate shader
    program->bind();
    
    // pass projection matrix to the shader
    glm::mat4 projection = glm::perspective(glm::radians(zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    program->setMat4("uProjection", projection);

    // camera/view transformation
    glm::mat4 view = camera.getViewMatrix();
    program->setMat4("uView", view);

    // render boxes
    // glBindVertexArray(VAO);
    // for(unsigned int i = 0; i < 10; i++)
    // {
    //     glm::mat4 model = glm::mat4(1.0f);
    //     model = glm::translate(model, cubePositions[i]);
    //     float angle = 20.0f * i;
    //     model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    //     program->setMat4("uModel", model);
    //     glDrawArrays(GL_TRIANGLES, 0, 36);
    // }

    for(int i = 0; i < NUM_ENTITIES; i++)
    {
        entities[i]->draw(*program);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

int main(int argc, char **argv)
{
    std::cout << "Grendel" << std::endl;

    // ================================================
    // GLFW INIT
    // ================================================
    std::cout << "- GLFW Init" << std::endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);    

    // ================================================
    // WINDOW
    // ================================================
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Grendel", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    // capture mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // ================================================
    // SHADER
    // ================================================
    program = new Program("/assets/shaders/texture_vertex.glsl", "/assets/shaders/texture_fragment.glsl");

    // ================================================
    // ENTITIES
    // ================================================
    for(int i=0; i<NUM_ENTITIES; i++)
    {
        entities.push_back(new Entity(i, "An entity", "/assets/textures/entity.png", glm::vec2((i * 2.0f), 0.0f)));
    }

    // ================================================
    // TEXTURE
    // ================================================
    // TODO : https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/7.4.camera_class/camera_class.cpp


    // ================================================
    // ENTER RENDER LOOP
    // ================================================
    std::cout << "Entering main loop" << std::endl;
    emscripten_set_main_loop(&main_loop, 0, true);
}
