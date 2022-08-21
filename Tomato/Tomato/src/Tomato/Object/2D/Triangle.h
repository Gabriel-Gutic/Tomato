#pragma once
#include "Object/Object.h"
#include "Renderer/Buffer/Vertex.h"


namespace Tomato
{
	class Triangle : public Object
	{
	public:
		Triangle();
		virtual ~Triangle() override = default;

		static const std::array<std::pair<Float2, Float2>, 3> Vertices;
	};
}
