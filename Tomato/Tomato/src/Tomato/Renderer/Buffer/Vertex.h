#pragma once
#include "Renderer/Texture/Texture.h"


namespace  Tomato
{
	struct Vertex
	{
		Float3 Coords;
		Float4 Color;
		float TexIndex;
		Float2 TexCoords;
		/*
		Type 0 -> Default Drawing;
		Type 1 -> Text Drawing;
		*/
		float Type;

		Vertex(const Float3& coords = Float3(0.0f, 0.0f, 0.0f), const Float4& color = Float4(1.0f, 1.0f, 1.0f, 1.0f), float texIndex = -1.0f, const Float2& texCoords = Float2(0.0f, 0.0f), float type = 0.0f)
			:Coords(coords), Color(color), TexIndex(texIndex), TexCoords(texCoords), Type(type)
		{}

		Vertex(const Vertex&);
		~Vertex() = default;

		Vertex& operator=(const Vertex& other)
		{
			// Guard self assignment
			if (this == &other)
				return *this;

			Coords = other.Coords;
			Color = other.Color;
			TexIndex = other.TexIndex;
			TexCoords = other.TexCoords;
			Type = other.Type;

			return *this;
		}

		std::string ToString() const;
	};
}