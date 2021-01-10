#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID; // ID for any object that we allocate for our vertexbuffer
	unsigned int m_Count; // we need to define how many indices we have
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count;  } // since its a very small function, to reduce overhead we use inline function, so whenever is called at compile-time the compiler will substitude this line with this function

};