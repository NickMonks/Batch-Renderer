#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map> // very useful for caching

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath; //print what file belongs to
	std::unordered_map<std::string, int> m_UniformLocationCache;
	// caching for uniforms 

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//set uniforms - there are a LOT. In the game engine we should use a set
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniform1fi(const std::string& name, int value);
	void setUniform1f(const std::string& name, float value);

private:

	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filepath);
	int GetUniformLocation(const std::string& name);
};
