#pragma once
#include "DirectXBuffer.h"
#include "Tomato/Renderer/Buffer/IndexBuffer.h"


namespace Tomato
{
#ifdef TOMATO_PLATFORM_WINDOWS
	class DirectXIndexBuffer : public IndexBuffer, public DirectXBuffer
	{
	public:
		DirectXIndexBuffer(uint32_t count, BufferAllocType allocType, const void* data = nullptr);
		virtual ~DirectXIndexBuffer() override;

		virtual void Bind() override;
	private:
		virtual void SetRawData(const void* data, uint32_t size) const override;
	};
#else
	class DirectXIndexBuffer : public IndexBuffer, public DirectXBuffer
	{
	public:
		DirectXIndexBuffer(uint32_t count, BufferAllocType allocType, const void* data = nullptr):IndexBuffer(allocType) {}
		virtual ~DirectXIndexBuffer() override {}

		virtual void Bind() override {}
	private:
		virtual void SetRawData(const void* data, uint32_t size) const override {}
	};
#endif // TOMATO_PLATFORM_WINDOWS
}
