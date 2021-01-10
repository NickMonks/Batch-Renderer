#pragma once
#include "Renderer.h"
#include <iostream>

 void GLClearError()
{
    while (glGetError() != GL_NO_ERROR); // clears all the errors
}

 bool GLLogCall(const char* function, const char* file, int line)
{
    // we return a bool and then depending on the macro it will or not stop execution
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] " << "(" << error << "):" << function <<
            " " << file << " : " << line << std::endl;
        return false;
    }
    return true;
}

 void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
 {
     shader.Bind();
     va.Bind();
     ib.Bind();

     GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr)); // takes whatever is bounded and draws it into the window

 }

 void Renderer::Clear() const
 {
     /* Render here */
     glClear(GL_COLOR_BUFFER_BIT);
 }