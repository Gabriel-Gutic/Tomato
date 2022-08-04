#pragma once


namespace  Tomato
{
	struct Vertex
	{
		Float3 Coords;
		Float4 Color;
		Float2 TexCoords;

		Vertex() = default;

		Vertex(const Float3& coords, const Float4& color = Float4(1.0f, 1.0f, 1.0f, 1.0f), const Float2& texCoords = Float2(0.0f, 0.0f))
			:Coords(coords), Color(color), TexCoords(texCoords)
		{}

		Vertex& operator=(const Vertex& other)
		{
			// Guard self assignment
			if (this == &other)
				return *this;
			
			Coords = other.Coords;
			Color = other.Color;
			TexCoords = other.TexCoords;

			return *this;
		}
	};
}
