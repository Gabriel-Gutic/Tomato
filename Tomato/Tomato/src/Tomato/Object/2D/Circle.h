#pragma once
#include "Renderer/Buffer/Vertex.h"
#include "Object/Object.h"


namespace Tomato
{
	class Circle : public Object
	{
	public:
		Circle(Float smoothness = 0.5f);
		Circle(const Circle& other);
		~Circle() = default;

		void SetSmoothness(Float smoothness);
		Float GetSmoothness() const;

		std::vector<Vertex> GetVertices();
		const std::vector<Vertex>& GetVertices() const;
		std::vector<UInt> GetIndices() const;
	private:
		Float m_Smoothness;
		std::vector<Vertex> m_Vertices;

		const UInt c_SmoothnessMultiply = 100;
	};
}
