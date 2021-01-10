#pragma once
#include <vector>
#include "Renderer.h"
#include <GL\glew.h>

struct VertexBufferElement
{
	// define the field values of the vertex attribute pointer for element element, assigned with the index
	unsigned int type;
	int count;
	unsigned char normalized;

	// static method, not associate with the instance of the struct. 
	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT         : return 4;
		case GL_UNSIGNED_INT  : return 4;
		case GL_UNSIGNED_BYTE : return 1;
		}
		ASSERT(false) // assert with the preprocessor
		return 0;

	}
};

// this class is an abstraction of vertex attribute pointer 
class VertexBufferLayout
{
	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
public:
	VertexBufferLayout()
		:m_Stride(0) {} // initialize our stride as 0 (i.e, the distance between the beginning of the same generic attribute)

	template<typename T>
	void Push(int count)
	{	
		// in case the type is unmatch we will not use this
		static_assert(false);
	}

	template<> 
	void Push<float>(int count)
	{
		m_Elements.push_back({GL_FLOAT,count, GL_FALSE});
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count; 
	}

	template<> // template specialization - not define type T and different calls for each type
	void Push<unsigned int>(int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT,count, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count; //4 bytes of memory


	}
	template<> // template specialization - not define type T and different calls for each type
	void Push<unsigned char>(int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE,count, GL_TRUE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;


	}

	inline std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }

};