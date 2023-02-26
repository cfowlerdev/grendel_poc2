#pragma once
#include <string>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>

class Texture2D
{
public:
    GLuint textureID;

    Texture2D(const std::string& p_filename, int slotId = 0);
    ~Texture2D();

    void bind();
    void unbind();

    inline int width() const { return _width; }
    inline int height() const { return _height; }
    inline GLuint texture() const { return textureID; }
private:
    int _slotId;
    int _width;
    int _height;
    int _bpp;
};