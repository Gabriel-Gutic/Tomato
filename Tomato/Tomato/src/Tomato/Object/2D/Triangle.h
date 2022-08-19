#pragma once
#include "Object/Object.h"
#include "Object/Color.h"
#include "Object/Transform.h"
#include "Renderer/Buffer/Vertex.h"


namespace Tomato
{
	class Triangle : public Object, public TransformInterface, public ColorInterface
	{
	public:
		Triangle();
		virtual ~Triangle() override = default;

		static const std::array<std::pair<Float2, Float2>, 3> Vertices;
	};
}


namespace YAML
{
	template<>
	struct convert<Tomato::Triangle> {
		static Node encode(const Tomato::Triangle& triangle) {
			Node node;
			node["Transform"] = triangle.GetTransform();
			return node;
		}
		static bool decode(const Node& node, Tomato::Triangle& triangle) {
			if (!node.IsMap()) {
				return false;
			}
			if (node["Transform"])
				triangle.SetTransform(node["Transform"].as<Tomato::Transform>());
			return true;
		}
	};
}
