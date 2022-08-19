#pragma once
#include "Object/Object.h"
#include "Object/Color.h"
#include "Object/Transform.h"
#include "Renderer/Buffer/Vertex.h"


namespace Tomato
{
	class Quad : public Object, public TransformInterface, public ColorInterface
	{
	public:
		Quad();
		virtual ~Quad() override = default;

		static const std::array<std::pair<Float2, Float2>, 4> Vertices;
		static const std::array<UInt, 6> Indices;
	};
}

namespace YAML
{
	template<>
	struct convert<Tomato::Quad> {
		static Node encode(const Tomato::Quad& quad) {
			Node node;
			node["Transform"] = quad.GetTransform();
			return node;
		}
		static bool decode(const Node& node, Tomato::Quad& quad) {
			if (!node.IsMap()) {
				return false;
			}
			if (node["Transform"])
				quad.SetTransform(node["Transform"].as<Tomato::Transform>());
			return true;
		}
	};
}


