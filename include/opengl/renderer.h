#pragma once
#include "opengl/vertexarray.h"
#include "opengl/indexbuffer.h"
#include "opengl/program.h"
#include "opengl/mesh.h"

class Renderer {
public:
    void draw(VertexArray& p_vertexArray, IndexBuffer& p_indexBuffer, Program& p_program);
    void draw(Mesh& p_mesh, Program& p_program);
};
