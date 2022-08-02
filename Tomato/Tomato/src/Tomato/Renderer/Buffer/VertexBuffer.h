#pragma once
#include "Buffer.h"
#include "Vertex.h"


namespace Tomato
{
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(std::initializer_list<Vertex> list);
		virtual ~VertexBuffer() override;

		virtual void Bind() override;
	private:
	};
}
