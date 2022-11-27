#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}

#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D u_Texture;

void main() { FragColor = texture(u_Texture, TexCoord); }