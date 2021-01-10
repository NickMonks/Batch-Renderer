#pragma once

#include <GL/glew.h>
#include "IndexBuffer.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"


// ----- DEFINE MACROS HERE ---------------------------
#define ASSERT(x) if (!(x)) __debugbreak(); //Use of the intrinsic compiler debug function
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__)) // #x will convert the function name into a string, and __file__ and __line__


void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

};

