#include "pchTomato.h"
#include "Vertex.h"


namespace Tomato
{
	std::string Vertex::ToString() const
	{
		std::stringstream ss;
		ss << "Vertex: Coords" << Coords.ToString() << ", Color" << Color.ToString() << ", TexCoords" << TexCoords.ToString();
		return ss.str();
	}
}


