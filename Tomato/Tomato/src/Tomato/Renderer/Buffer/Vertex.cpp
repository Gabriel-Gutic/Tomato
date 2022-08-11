#include "pchTomato.h"
#include "Vertex.h"


namespace Tomato
{
	Vertex::Vertex(const Vertex& other)
	{
		Coords = other.Coords;
		Color = other.Color;
		TexID = other.TexID;
		TexCoords = other.TexCoords;
	}

	std::string Vertex::ToString() const
	{
		std::stringstream ss;
		ss << "Vertex: Coords" << Coords.ToString() << ", Color" << Color.ToString() << ", TexCoords" << TexCoords.ToString();
		return ss.str();
	}
}


