#pragma once
#include "Renderer/Buffer/Vertex.h"
#include "Renderer/Scene/Entity.h"


namespace Tomato
{
	class Triangle : public Entity
	{
	public:
		Triangle();
		virtual ~Triangle() override = default;

		static const std::array<std::pair<Float2, Float2>, 3> Vertices;
	};
}
