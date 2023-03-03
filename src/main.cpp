#include <iostream>
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "engine.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

// ===========================================
// EMSCRIPTEN MAIN LOOP
// ===========================================
std::function<void()> loop;
void main_loop()
{
    loop();
}

int main(int argc, char **argv)
{
    std::cout << "Grendel" << std::endl;

    Engine engine("Grendel", WINDOW_WIDTH, WINDOW_HEIGHT);

    std::cout << "Entering main loop" << std::endl;
    loop = [&] {
        engine.render();
    };
    emscripten_set_main_loop(&main_loop, 0, true);
}
