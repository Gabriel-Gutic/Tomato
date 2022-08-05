#include "pchTomato.h"
#include "Triangle.h"


namespace Tomato
{
	void Triangle::Init(const Float3& A, const Float3& B, const Float3& C)
	{
		Float4 color = Float4(0.5f, 0.5f, 0.5f, 1.0f);
		m_Vertices[0] = Vertex(A, color, Float2(0.5f, 1.0f));
		m_Vertices[1] = Vertex(B, color, Float2(0.0f, 0.0f));
		m_Vertices[2] = Vertex(C, color, Float2(1.0f, 0.0f));
	}

	Triangle::Triangle(const Float3& A, const Float3& B, const Float3& C)
	{
		Init(A, B, C);
	}

	Triangle::Triangle(const Float3& center, Float radius)
	{
		Float3 A = Float3(center.x, center.y + radius, center.z);
		Float3 B = Float3(center.x - radius * (Float)sqrt(3) / 2.0f, center.y - radius / 2.0f, center.z);
		Float3 C = Float3(center.x + radius * (Float)sqrt(3) / 2.0f, center.y - radius / 2.0f, center.z);
	
		Init(A, B, C);
	}

	Mat4 Triangle::GetTransform() const
	{
		// Translate * Rotate * Scale
		Mat4 result = Math::Translate(m_Transform.Position);
		result = result * Math::Rotate(90.0f);
		result =  result * Math::Scale(m_Transform.Scale);

		return result;
	}

	std::vector<UInt> Triangle::GetIndices() const
	{
		return { 0, 1, 2 };
	}
}