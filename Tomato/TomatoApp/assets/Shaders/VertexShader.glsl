#version 330 core
layout (location = 0) in vec3 inCoords;
layout (location = 1) in vec4 inColor;

out vec4 outColor;

void main()
{
	outColor = inColor;
	gl_Position = vec4(inCoords, 1.0f);
}
