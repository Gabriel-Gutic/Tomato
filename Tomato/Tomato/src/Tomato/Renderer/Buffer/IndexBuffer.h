#pragma once
#include "Buffer.h"


namespace Tomato
{
	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(UInt mvn);
		virtual ~IndexBuffer() override;

		virtual void Bind() override;

		template <size_t MAX_SIZE>
		void SetData(const std::array<UInt, MAX_SIZE>& data, UInt count);
	private:
		void SetRawData(const UInt* data, UInt size) const;
	};

	template<size_t MAX_SIZE>
	inline void IndexBuffer::SetData(const std::array<UInt, MAX_SIZE>& data, UInt count)
	{
		SetRawData(data.data(), count * sizeof(UInt));
	}
}
