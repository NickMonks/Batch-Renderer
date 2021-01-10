#include "VertexBuffer.h"
#include "Renderer.h";

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_RendererID); // creates an ID for the generated buffer, which is pointing to wherever we use it
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); //selects the buffer. we say that the buffer is an array. 
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); //data is treated as a pointer to any type
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const 
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); //selects the buffer. we say that the buffer is an array. 
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0); //to unbind the object, we call it zero. 

}
