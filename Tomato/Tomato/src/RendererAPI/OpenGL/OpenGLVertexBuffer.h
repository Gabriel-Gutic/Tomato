#pragma once
#include "Tomato/Renderer/Buffer/VertexBuffer.h"
#include "OpenGLBuffer.h"


namespace Tomato
{
	class OpenGLVertexBuffer : public VertexBuffer, public OpenGLBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size, BufferAllocType allocType, const void* data = nullptr);
		virtual ~OpenGLVertexBuffer() override;

		virtual void Bind() override;
	private:
		virtual void SetRawData(const void* data, unsigned int size) const override;
	};
}
