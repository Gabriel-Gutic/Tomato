#pragma once
#include "OpenGLBuffer.h"
#include "Tomato/Renderer/Buffer/IndexBuffer.h"


namespace Tomato
{
	class OpenGLIndexBuffer : public IndexBuffer, public OpenGLBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t count, BufferAllocType allocType, const void* data = nullptr);
		virtual ~OpenGLIndexBuffer() override;

		virtual void Bind() override;
	private:
		virtual void SetRawData(const void* data, uint32_t size) const override;
	};
}
