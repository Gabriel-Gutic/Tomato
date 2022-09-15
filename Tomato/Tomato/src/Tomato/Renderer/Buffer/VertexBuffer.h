#pragma once
#include "Buffer.h"
#include "Vertex.h"


namespace Tomato
{
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(unsigned int size);
		virtual ~VertexBuffer() override;

		virtual void Bind() override;

		template <size_t MAX_SIZE>
		void SetData(const std::array<Vertex, MAX_SIZE>& data, unsigned int count);
		template <size_t MAX_SIZE>
		void SetData(const std::array<Mesh::Vertex, MAX_SIZE>& data, unsigned int count);
	private:
		void SetRawData(const void* data, unsigned int size) const;
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
