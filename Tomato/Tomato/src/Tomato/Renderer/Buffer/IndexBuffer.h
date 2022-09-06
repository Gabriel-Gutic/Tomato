#pragma once
#include "Buffer.h"


namespace Tomato
{
	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(unsigned int mvn);
		virtual ~IndexBuffer() override;

		virtual void Bind() override;

		template <size_t MAX_SIZE>
		void SetData(const std::array<unsigned int, MAX_SIZE>& data, unsigned int count);
	private:
		void SetRawData(const unsigned int* data, unsigned int size) const;
	};

	template<size_t MAX_SIZE>
	inline void IndexBuffer::SetData(const std::array<unsigned int, MAX_SIZE>& data, unsigned int count)
	{
		SetRawData(data.data(), count * sizeof(unsigned int));
	}
}
