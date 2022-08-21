#include "pchTomato.h"
#include "Quad.h"
#include "Component/Transform.h"
#include "Component/Color.h"

namespace Tomato
{
    Quad::Quad()
    {
		AddComponent(std::make_shared<Transform>());
		AddComponent(std::make_shared<Color>());
    }

	const std::array<std::pair<Float2, Float2>, 4> Quad::Vertices = {
			std::make_pair(Float2(-0.5f, -0.5f), Float2(0.0f, 0.0f)),
			std::make_pair(Float2(-0.5f,  0.5f), Float2(0.0f, 1.0f)),
			std::make_pair(Float2( 0.5f, -0.5f), Float2(1.0f, 0.0f)),
			std::make_pair(Float2( 0.5f,  0.5f), Float2(1.0f, 1.0f)),
	};

	const std::array<UInt, 6> Quad::Indices = {
			0, 1, 2,
			2, 1, 3
	};
}