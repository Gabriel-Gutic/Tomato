#version 330 core

in vec4 Color;
in float TexIndex;
in vec2 TexCoords;
in vec4 Position;

out vec4 FragColor;

uniform sampler2D u_Textures[32];

void main()
{
	vec2 coords = (gl_FragCoord.xy / 800.0f) * 2.0f - 1.0f;
	float distance = 1.0f - distance(coords, vec2(0.0f));

	if (Position.x * Position.x + Position.y * Position.y > 0.7f)
		discard;
	FragColor = vec4(vec3(distance), 1.0);
}

