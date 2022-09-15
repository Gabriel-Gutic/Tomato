#version 330 core
layout (location = 0) in vec3 Position;
layout (location = 1) in vec4 Color;
layout (location = 2) in vec3 Normal;
layout (location = 3) in vec2 TexCoords;

uniform mat4 u_VP;

out vec4 o_Color;
out vec2 o_TexCoords;


void main()
{
	o_Color = Color;
	o_TexCoords = TexCoords;
	gl_Position = u_VP * vec4(Position, 1.0f);
}
