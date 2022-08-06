#pragma once
#include "Object.h"
#include "Transform.h"
#include "Renderer/Buffer/Vertex.h"


namespace Tomato
{
	class Quad : public Object, public TransformInterface, public VertexInterface<4>
	{
	public:
		Quad();
		virtual ~Quad() override;

		std::vector<UInt> GetIndices() const;
	};
}
