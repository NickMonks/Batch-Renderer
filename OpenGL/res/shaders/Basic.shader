#shader vertex
#version 330 core

layout(location = 0) in vec4 position; //0 is the index of our attribute; vec4 is used for position, itwill cast as a union to a vec2
layout(location = 1) in vec2 texCoord; // 1 the other layout buffer, which is the texture coordinate system for our vertex. 

out vec2 v_TexCoord; // this is how we pass data from shaders; define a vec2 as out, and return it

void main() 
{
   gl_Position = position; // here we define our vertex attribute, which is the attribute in index 0
   v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color; //0 is the index of our attribute; vec4 is used for position, itwill cast as a union to a vec2

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture; // sampler to interpolate the texture

void main() 
{	
	// tex tobesample, and texCoord, which is defined in the layout of vertex shader. 
	// to share data between shaders we use the varying. 
	// after that, we interpolate

	vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor; // here we define our vertex attribute, which is the attribute in index 0
};