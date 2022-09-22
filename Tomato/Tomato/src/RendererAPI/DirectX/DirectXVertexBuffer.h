#pragma once
#include "DirectXBuffer.h"
#include "Tomato/Renderer/Buffer/VertexBuffer.h"


namespace Tomato
{
#ifdef TOMATO_PLATFORM_WINDOWS
	class DirectXVertexBuffer : public DirectXBuffer, public VertexBuffer
	{
	public:
		DirectXVertexBuffer(uint32_t size, BufferAllocType allocType, const void* data = nullptr);
		virtual ~DirectXVertexBuffer() override;

		virtual void Bind() override;
	private:
		virtual void SetRawData(const void* data, unsigned int size) const override;
	};
#else
	class DirectXVertexBuffer : public DirectXBuffer, public VertexBuffer
	{
	public:
		DirectXVertexBuffer(uint32_t size, BufferAllocType allocType, const void* data = nullptr) :VertexBuffer(allocType) {}
		virtual ~DirectXVertexBuffer() override {}

		virtual void Bind() override {}
	private:
		virtual void SetRawData(const void* data, unsigned int size) const override {}
	};
#endif
}
