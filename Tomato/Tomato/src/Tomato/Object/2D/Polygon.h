#pragma once
#include "Renderer/Buffer/Vertex.h"
#include "Object/Transform.h"
#include "Object/Object.h"


namespace Tomato
{
	class Polygon : public Object, public TransformInterface
	{
	public:
		Polygon(UInt numberOfSides = 6);
		virtual ~Polygon() = default;

		void SetNumberOfSides(UInt numberOfSides);
		UInt GetNumberOfSides() const;

		std::vector<Vertex> GetVertices();
		const std::vector<Vertex>& GetVertices() const;
		std::vector<UInt> GetIndices() const;
	protected:
		UInt m_NumberOfSides;
		std::vector<Vertex> m_Vertices;
	};
}
