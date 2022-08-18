#pragma once
#include "Renderer/Buffer/Vertex.h"
#include "Object/Object.h"
#include "Object/Transform.h"
#include "Object/Color.h"


namespace Tomato
{
	class Circle : public Object, public ColorInterface, public TransformInterface
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


namespace YAML
{
	template<>
	struct convert<Tomato::Circle> {
		static Node encode(const Tomato::Circle& circle) {
			Node node;
			node["Transform"] = circle.GetTransform();
			node["Smoothness"] = circle.GetSmoothness();
			node["Color"] = circle.GetColor();
			return node;
		}
		static bool decode(const Node& node, Tomato::Circle& circle) {
			if (!node.IsMap()) {
				return false;
			}
			if (node["Transform"])
				circle.SetTransform(node["Transform"].as<Tomato::Transform>());
			if (node["Smoothness"])
				circle.SetSmoothness(node["Smoothness"].as<Tomato::Float>());
			if (node["Color"])
				circle.SetColor(node["Color"].as<Tomato::Color>());
			return true;
		}
	};
}
