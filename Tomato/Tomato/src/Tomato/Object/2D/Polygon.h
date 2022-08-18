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
			return node;
		}
		static bool decode(const Node& node, Tomato::Polygon& poly) {
			if (!node.IsMap()) {
				return false;
			}

			poly.SetTransform(node["Transform"].as<Tomato::Transform>());
			return true;
		}
	};
}
