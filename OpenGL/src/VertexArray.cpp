#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"


// create a vertex array object. In core mode for OPENGL this is actually necessary, so we bind it.
// with the vao, we can bind the actual buffer and the layout (the vertexattr), so we dont need to specify
// the same vertexattr for other objects.

// how is the array buffer bind to this VAO?, the vertexattr specifies an index, which bounds the vertex array and the buffer array.
//So, if vertexattr contained index 1, will mean that the vertexarray index 1 will point to that vertex buffer that is bounded.

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	GLCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{	
	// first we bind the vertex array itself. For each instance it will bind himself
	Bind();
	// then we bind the buffer
	vb.Bind();

	// and finally our layout. So,  soon as you've bound a certain VAO, every time you call glVertexAttribPointer, that information will be stored in that VAO. This makes switching between
	// different vertex data and vertex formats as easy as binding a different VAO. 

	
	const auto& elements = layout.GetElements(); // we want to reference of that member container vector. element will be: color, texture, etc. 
	unsigned int offset = 0; // this is the offset (or pointer) between attributes

	for (unsigned int i = 0; i < elements.size(); i++)
	{

		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, 
								element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type); // the stride will be the count of element that we have, the f(x)=x+n, n is the pointer  
	}
	
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID)); // binds to the vao object created, where vao is nothing more than a pointer 
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));

}