#pragma once

#include "Renderer.h"

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer; //local storage for the texture
	int m_Width, m_Height, m_BPP; // bits per pixel of the texture

public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	// slots to bind the texture to. We can bind more than one texture at the time.
	// in Win 32 and mobile around 8. 
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

};