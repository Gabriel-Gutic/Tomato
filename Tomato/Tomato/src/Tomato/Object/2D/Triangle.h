#pragma once
#include "Object/Object.h"
#include "Object/Transform.h"
#include "Renderer/Buffer/Vertex.h"


namespace Tomato
{
	class Triangle : public Object, public TransformInterface, public VertexInterface<3>
	{
	private:
		void Init(const Float3& A, const Float3& B, const Float3& C);
	public:
		Triangle(const Float3& A = Float3(0.0f, 0.5f, 0.0f), const Float3& B = Float3(-0.5f, -0.5f, 0.0f), const Float3& C = Float3(0.5f, -0.5f, 0.0f));
		Triangle(const Float3& center, Float radius);
		virtual ~Triangle() = default;

		virtual std::vector<UInt> GetIndices() const;
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
