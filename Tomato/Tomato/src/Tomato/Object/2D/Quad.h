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
