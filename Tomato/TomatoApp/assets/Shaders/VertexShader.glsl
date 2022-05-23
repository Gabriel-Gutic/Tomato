#version 330 core
layout (location = 0) in vec3 inPos;

out vec3 outColor;

void main()
{
	outColor = inPos;
	gl_Position = vec4(inPos, 1.0f);
}
