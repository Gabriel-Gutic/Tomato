#pragma once
#include "Renderer/Buffer/Vertex.h"
#include "Renderer/Scene/Entity.h"


namespace Tomato
{
	class Polygon : public Entity
	{
	public:
		Polygon(UInt numberOfSides = 6);
		virtual ~Polygon() = default;

		void SetNumberOfSides(UInt numberOfSides);
		UInt GetNumberOfSides() const;

		std::vector<Vertex> GetVertices();
		const std::vector<Vertex>& GetVertices() const;
		std::vector<UInt> GetIndices() const;

		static std::vector<Float2> GenerateCoords(UInt numberOfSides);
	protected:
		UInt m_NumberOfSides;
		std::vector<Vertex> m_Vertices;
	};
}
