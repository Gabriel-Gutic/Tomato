#include "pchTomato.h"
#include "Triangle.h"


namespace Tomato
{
	Triangle::Triangle()
	{
	}

	const std::array<std::pair<Float2, Float2>, 3> Triangle::Vertices = {
		std::make_pair(Float2(0.0f, -0.5f + sqrtf(3) / 2.0f), Float2(0.5f, 1.0f)),
		std::make_pair(Float2(-0.5f, -0.5f), Float2(0.0f, 0.0f)),
		std::make_pair(Float2(0.5f, -0.5f), Float2(1.0f, 0.0f)),
	};
}