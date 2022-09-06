#pragma once
#include "Buffer.h"
#include "Vertex.h"


namespace Tomato
{
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(unsigned int mvn);
		virtual ~VertexBuffer() override;

		virtual void Bind() override;

		template <size_t MAX_SIZE>
		void SetData(const std::array<Vertex, MAX_SIZE>& data, unsigned int count);
	private:
		void SetRawData(const Vertex* data, unsigned int size) const;
	};

	template<size_t MAX_SIZE>
	inline void VertexBuffer::SetData(const std::array<Vertex, MAX_SIZE>& data, unsigned int count)
	{
		SetRawData(data.data(), count * sizeof(Vertex));
	}
}
