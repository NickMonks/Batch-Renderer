#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID; // ID for any object that we allocate for our vertexbuffer
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;


};