#version 330 core

in vec4 o_Color;
in vec2 o_TexCoords;

out vec4 FragColor;

void main()
{
	FragColor = o_Color;
}

