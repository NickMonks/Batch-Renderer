#include "IndexBuffer.h"
#include "Renderer.h";

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint)); // This is added to assert that both types are the same in cross-platform

    glGenBuffers(1, &m_RendererID); // creates an ID for the generated buffer, which is pointing to wherever we use it
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); //selects the buffer. we say that the buffer is an array. 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW); //data is treated as a pointer to any type
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); //selects the buffer. we say that the buffer is an array. 
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //to unbind the object, we call it zero. 

}
