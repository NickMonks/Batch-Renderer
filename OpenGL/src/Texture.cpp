#include "Texture.h"
#include "vendor/stb_image/stb_image.h"


Texture::Texture(const std::string& path)
	:m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1); // this flips the texture vertically, openGL expects us to start at bottom-left, but images does on the top (PNG)
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP,4); // channels is RBGA, so its 4

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	// settings for our texture, with the data we want to add.
	// texture min texture is how we will change the texture if we need to reduce it
	//we need to define, al least, this 4 parameters!
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	// format vs internal format: internal is the format that OpenGL interprets (also, prvide the n of bits), and format is the data you provide. 
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	// we free the buffer data, once we have bind it in the GL_TEXTURE_2D
	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);


}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	// we specify the texture slot to activate
	// state machine : i'm binding that slot, selecting that one and it will be in this state,
	// until I call glbind again
	GLCall(glActiveTexture(GL_TEXTURE0 + slot)); // slot will add the slot we want, if 5 then slot  5 selected
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}