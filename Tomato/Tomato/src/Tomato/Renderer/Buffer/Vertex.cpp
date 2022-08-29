#include "pchTomato.h"
#include "Vertex.h"


namespace Tomato
{
	Vertex::Vertex(const Vertex& other)
	{
		Coords = other.Coords;
		Color = other.Color;
		TexIndex = other.TexIndex;
		TexCoords = other.TexCoords;
		Type = other.Type;
	}

	std::string Vertex::ToString() const
	{
		std::stringstream ss;
		ss << "Vertex: Coords" << Coords.ToString() << ", Color" << Color.ToString() << ", TexIndex(" << TexIndex << "), TexCoords" << TexCoords.ToString() << ", Type(" << Type << ")";
		return ss.str();
	}
}


