#version 330 core
layout (location = 0) in vec3 inCoords;
layout (location = 1) in vec4 inColor;
layout (location = 2) in float inTexIndex;
layout (location = 3) in vec2 inTexCoords;

uniform mat4 u_PV;

out vec4 Color;
out float TexIndex;
out vec2 TexCoords;


void main()
{
	Color = inColor;
	TexIndex = inTexIndex;
	TexCoords = inTexCoords;
	gl_Position = u_PV * vec4(inCoords, 1.0f);
}
