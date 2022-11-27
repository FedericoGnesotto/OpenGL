#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 out_color0;    // output variable for color attachment 0

in vec2 TexCoord;

uniform sampler2D u_InputTexture;

void main() { out_color0 = 1.0 * texture(u_InputTexture, TexCoord); }