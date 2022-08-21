#pragma once
#include "Object/Object.h"
#include "Renderer/Buffer/Vertex.h"


namespace Tomato
{
	class Quad : public Object
	{
	public:
		Quad();
		virtual ~Quad() override = default;

		static const std::array<std::pair<Float2, Float2>, 4> Vertices;
		static const std::array<UInt, 6> Indices;
	};
}


