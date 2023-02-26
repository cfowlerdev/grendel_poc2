#include "opengl/vertexarray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &id);
}

void VertexArray::addBuffer(VertexBuffer& p_vertexBuffer, const VertexBufferLayout& layout)
{
    bind();
    p_vertexBuffer.bind();

    // TODO: could this be done in a nicer/cleaner way?
    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.getStride(), (const void*)(size_t) offset);
        offset += element.count * VertexBufferLayoutElement::getSizeOfType(element.type);
    }
}

void VertexArray::bind()
{
    glBindVertexArray(id);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}
