#version 330 core
layout (location = 0) in vec3 inCoords;
layout (location = 1) in vec4 inColor;
layout (location = 2) in float inTexIndex;
layout (location = 3) in vec2 inTexCoords;

uniform mat4 u_Projection;
uniform mat4 u_View;

out vec4 Color;
out float TexIndex;
out vec2 TexCoords;
out vec4 Position;


void main()
{
	Color = inColor;
	TexIndex = inTexIndex;
	TexCoords = inTexCoords;
	gl_Position = u_Projection * u_View * vec4(inCoords, 1.0f);
	Position = gl_Position;
}
