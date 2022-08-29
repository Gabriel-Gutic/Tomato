#version 330 core

in vec4 Color;
in float TexIndex;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D u_Textures[32];

void main()
{
	if (TexIndex < 0)
		FragColor = Color;
	else 
	{
		int index = int(TexIndex + 0.1f);

		vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_Textures[index], TexCoords).r);
		FragColor = Color * sampled;
	}
}
