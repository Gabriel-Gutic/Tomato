#version 330 core

in vec4 Color;
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D Texture;

void main()
{
	FragColor = Color;
	//FragColor = texture(Texture, TexCoords);
}

