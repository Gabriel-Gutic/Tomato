#version 330 core

in vec4 Color;
in float TexID;
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D u_Textures[8];

void main()
{
	if (TexID < 0)
		FragColor = Color;
	else 
	{
		highp int index = int(TexID + 0.1f);
		FragColor = texture(u_Textures[index], TexCoords);
	}
}

