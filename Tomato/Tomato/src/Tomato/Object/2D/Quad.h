#pragma once
#include "Object/Object.h"
#include "Object/Transform.h"
#include "Renderer/Buffer/Vertex.h"


namespace Tomato
{
	class Quad : public Object, public TransformInterface, public VertexInterface<4>
	{
	public:
		Quad();
		virtual ~Quad() override;

		virtual std::vector<UInt> GetIndices() const;
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


