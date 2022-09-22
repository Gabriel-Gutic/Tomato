#pragma once
#include "DirectXBuffer.h"
#include "Tomato/Renderer/Buffer/IndexBuffer.h"


namespace Tomato
{
	class DirectXIndexBuffer : public IndexBuffer, public DirectXBuffer
	{
	public:
		DirectXIndexBuffer(uint32_t count, BufferAllocType allocType, const void* data = nullptr);
		virtual ~DirectXIndexBuffer() override;

		virtual void Bind() override;
	private:
		virtual void SetRawData(const void* data, uint32_t size) const override;
	};
}
