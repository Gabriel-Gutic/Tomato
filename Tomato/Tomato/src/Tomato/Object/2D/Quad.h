#pragma once
#include "Renderer/Buffer/Vertex.h"
#include "Renderer/Scene/Entity.h"


namespace Tomato
{
	class Quad : public Entity
	{
	public:
		Quad();
		virtual ~Quad() override = default;

		static const std::array<std::pair<Float2, Float2>, 4> Vertices;
		static const std::array<UInt, 6> Indices;
	};
}


