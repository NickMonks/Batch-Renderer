#include "Shader.h"
#include "Renderer.h"

Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_RendererID(0)
{	
	//Shaders: program that runs on the GPU. Block of code that can be read as a stream; the difference is that runs in the gpu
		// -Vertex shaders: glvert
		// - Fragment shaders: pixels

		// creating our first shader!

	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID= CreateShader(source.VertexSource, source.FragmentSource);
	
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));

}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath); // this opens the stream file

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};


	std::string line;
	std::stringstream ss[2]; // we create two write streams (write = outstream)
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {

		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;

		}
		else
		{
			ss[(int)type] << line << '\n'; // we explicitly cast the enum to int and add in the stream the line
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str(); //!!! make sure source it exists, dont use GetString(0 which creates temporal string and char* will return garbage
						   //pointer to our pointer source code
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	// TODO: error handling 

	glGetShaderiv(id, GL_COMPILE_STATUS, &result); // ivs means that it needs an integer  vector.

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" <<
			(type == GL_VERTEX_SHADER ? "vertex shader" : "vertex fragment")
			<< std::endl;
		// delete shader since compilation didn't work out
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{

	// provide openGL with the actual source code, as a shader text
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs); // delete intermidiate files
	glDeleteShader(fs); // delete intermidiate files

	return program;

	//Compile that program

	//link both shader for a single program

	// return an int as a shader identifier

}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}



void Shader::setUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::setUniform1fi(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	// to define data in the shader, after binding it we use uniforms
	// in our case, is a vec4 which are 4 floats and we call glUniform4f
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str())); // since we are constantly retrieving the same location again and again, we will cache it
	//ASSERT(location != -1); // if it's less than 0 means it doesnt found.
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesnt exist!" << std::endl;
	
	m_UniformLocationCache[name] = location;
	return location;
}



