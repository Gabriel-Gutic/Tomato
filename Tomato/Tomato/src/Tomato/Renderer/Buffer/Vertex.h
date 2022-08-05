#pragma once


namespace  Tomato
{
	struct Vertex
	{
		Float3 Coords;
		Float4 Color;
		Float2 TexCoords;

		Vertex(const Float3& coords = Float3(0.0f, 0.0f, 0.0f), const Float4& color = Float4(1.0f, 1.0f, 1.0f, 1.0f), const Float2& texCoords = Float2(0.0f, 0.0f))
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

	template <size_t COUNT>
	class VertexInterface
	{
	public:
		const std::array<Vertex, COUNT>& GetVertices() const;
		std::array<Vertex, COUNT>& GetVertices();
	protected:
		std::array<Vertex, COUNT> m_Vertices;
	};

	template<size_t COUNT>
	inline const std::array<Vertex, COUNT>& VertexInterface<COUNT>::GetVertices() const
	{
		return m_Vertices;
	}

	template<size_t COUNT>
	inline std::array<Vertex, COUNT>& VertexInterface<COUNT>::GetVertices()
	{
		return m_Vertices;
	}
}
