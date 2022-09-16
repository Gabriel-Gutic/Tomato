#pragma once
#include "Buffer.h"
#include "Vertex.h"


namespace Tomato
{
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(BufferAllocType allocType);
		virtual ~VertexBuffer() override = default;


		template <size_t MAX_SIZE>
		void SetData(const std::array<Vertex, MAX_SIZE>& data, uint32_t count);
		template <size_t MAX_SIZE>
		void SetData(const std::array<Mesh::Vertex, MAX_SIZE>& data, uint32_t count);
	public:
		static std::unique_ptr<VertexBuffer> CreateUnique(uint32_t size, BufferAllocType allocType, const void* data = nullptr);
		static std::shared_ptr<VertexBuffer> CreateShared(uint32_t size, BufferAllocType allocType, const void* data = nullptr);
	private:
		virtual void SetRawData(const void* data, unsigned int size) const = 0;
	};

	template<size_t MAX_SIZE>
	inline void VertexBuffer::SetData(const std::array<Vertex, MAX_SIZE>& data, unsigned int count)
	{
		SetRawData(data.data(), count * sizeof(Vertex));
	}

	template<size_t MAX_SIZE>
	inline void VertexBuffer::SetData(const std::array<Mesh::Vertex, MAX_SIZE>& data, unsigned int count)
	{
		SetRawData(data.data(), count * sizeof(Mesh::Vertex));
	}
}
