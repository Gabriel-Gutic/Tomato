#include "pchTomato.h"
#include "Quad.h"


namespace Tomato
{
    Quad::Quad()
    {
		m_Vertices[0] = Vertex(Float3(-1.0f, -1.0f, 0.0f));
		m_Vertices[1] = Vertex(Float3(-1.0f,  1.0f, 0.0f));
		m_Vertices[2] = Vertex(Float3( 1.0f, -1.0f, 0.0f));
		m_Vertices[3] = Vertex(Float3( 1.0f,  1.0f, 0.0f));
    }

    Quad::~Quad()
    {
    }

    std::vector<UInt> Quad::GetIndices() const
    {
        return 
        { 
            0, 1, 2, 
            1, 2, 3
        };
    }

}