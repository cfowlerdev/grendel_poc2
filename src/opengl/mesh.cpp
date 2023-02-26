#include "opengl/mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
    : vertices(vertices), indices(indices), textures(textures)
{
    _vao = new VertexArray();
    _vbo = new VertexBuffer(&this->vertices[0], vertices.size() * sizeof(Vertex));
    _ibo = new IndexBuffer(&this->indices[0], indices.size());
    generateMesh();
}

void Mesh::generateMesh()
{
    _vao->bind();
    _vbo->bind();
    _ibo->bind();
    VertexBufferLayout layout;
    layout.push<float>(3);      // vertex pos
    layout.push<float>(3);      // vertex normals
    layout.push<float>(2);      // vertex texture coords
    layout.push<float>(3);      // tangent
    layout.push<float>(3);      // bi-tangent
    _vao->addBuffer(*_vbo, layout);
    _vao->unbind();
}  

void Mesh::bindResources(Program& p_program)
{
    p_program.bind();

    GLuint diffuseNumber = 0;
    GLuint normalNumber = 1;
    GLuint metalRoughnessNumber = 2;

    for(GLuint i=0; i < this->textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string name = this->textures[i].type;
        glUniform1i(p_program.getUniform((name).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
    }
}

void Mesh::draw(Program& p_program)
{
    bindResources(p_program);
    _vao->bind();
    _ibo->bind();
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    _vao->unbind();
    _ibo->unbind();
}
