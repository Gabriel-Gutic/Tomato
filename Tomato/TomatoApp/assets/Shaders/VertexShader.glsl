#version 330 core
layout (location = 0) in vec2 inPos;

out vec3 outColor;

void main()
{
	outColor = vec3(inPos, 0.5f);
	gl_Position = vec4(inPos, 0.0f, 1.0f);
}
