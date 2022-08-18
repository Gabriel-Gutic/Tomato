#pragma once
#include "Renderer/Buffer/Vertex.h"
#include "Object/Transform.h"
#include "Object/Color.h"
#include "Object/Object.h"


namespace Tomato
{
	class Polygon : public Object, public TransformInterface, public ColorInterface
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


namespace YAML
{
	template<>
	struct convert<Tomato::Polygon> {
		static Node encode(const Tomato::Polygon& poly) {
			Node node;
			node["Transform"] = poly.GetTransform();
			node["Sides"] = poly.GetNumberOfSides();
			node["Color"] = poly.GetColor();
			return node;
		}
		static bool decode(const Node& node, Tomato::Polygon& poly) {
			if (!node.IsMap()) {
				return false;
			}

			if (node["Transform"])
				poly.SetTransform(node["Transform"].as<Tomato::Transform>());
			if (node["Sides"])
				poly.SetNumberOfSides(node["Sides"].as<Tomato::UInt>());
			if (node["Color"])
				poly.SetColor(node["Color"].as<Tomato::Color>());
			return true;
		}
	};
}
