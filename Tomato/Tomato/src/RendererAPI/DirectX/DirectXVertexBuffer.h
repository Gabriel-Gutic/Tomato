#pragma once
#include "DirectXBuffer.h"
#include "Tomato/Renderer/Buffer/VertexBuffer.h"


namespace Tomato
{
	class DirectXVertexBuffer : public DirectXBuffer, public VertexBuffer
	{
	public:
		DirectXVertexBuffer(uint32_t size, BufferAllocType allocType, const void* data = nullptr);
		virtual ~DirectXVertexBuffer() override;

		virtual void Bind() override;
	private:
		virtual void SetRawData(const void* data, unsigned int size) const override;
	};
}
