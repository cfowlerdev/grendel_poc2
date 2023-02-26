#include "opengl/renderer.h"

void Renderer::draw(VertexArray& p_vertexArray, IndexBuffer& p_indexBuffer, Program& p_program)
{
    p_program.bind();
    p_vertexArray.bind();
    p_indexBuffer.bind();

    glDrawElements(GL_TRIANGLES, p_indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::draw(Mesh& p_mesh, Program& p_program)
{
    p_mesh.draw(p_program);
}
