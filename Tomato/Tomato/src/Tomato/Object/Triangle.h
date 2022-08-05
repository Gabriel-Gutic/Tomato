#pragma once
#include "Object.h"
#include "Transform.h"
#include "Renderer/Buffer/Vertex.h"


namespace Tomato
{
	class Triangle : public Object
	{
	private:
		void Init(const Float3& A, const Float3& B, const Float3& C);
	public:
		Triangle(const Float3& A = Float3(0.0f, 0.5f, 0.0f), const Float3& B = Float3(-0.5f, -0.5f, 0.0f), const Float3& C = Float3(0.5f, -0.5f, 0.0f));
		Triangle(const Float3& center, Float radius);
		virtual ~Triangle() = default;

		const std::array<Vertex, 3>& GetVertices() const;
		std::array<Vertex, 3>& GetVertices();

		//Transform
		void SetPosition(const Float3& position);
		void SetScale(const Float3& scale);
		void SetRotation(const Float3& rotation);

		Mat4 GetTransform() const;
	private:
		std::array<Vertex, 3> m_Vertices;

		Transform m_Transform;
	};
}
