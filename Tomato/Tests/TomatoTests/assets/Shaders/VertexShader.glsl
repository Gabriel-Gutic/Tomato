#version 330 core
layout (location = 0) in vec3 inCoords;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inTexCoords;

out vec4 Color;
out vec2 TexCoords;

void main()
{
	Color = inColor;
	TexCoords = inTexCoords;
	gl_Position = vec4(inCoords, 1.0f);
}