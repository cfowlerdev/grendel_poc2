#pragma once
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "opengl/vertexbuffer.h"
#include "opengl/vertexbufferlayout.h"

class VertexArray
{
public:
    GLuint id;

    VertexArray();
    ~VertexArray();

    void addBuffer(VertexBuffer& p_vertexBuffer, const VertexBufferLayout& p_layout);

    void bind();
    void unbind();

};
