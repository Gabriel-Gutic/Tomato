#pragma once
#include "Buffer.h"


namespace Tomato
{
	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(BufferAllocType allocType);
		virtual ~IndexBuffer() override;

		template <size_t MAX_SIZE>
		void SetData(const std::array<uint32_t, MAX_SIZE>& data, uint32_t count);

	public:
		static std::unique_ptr<IndexBuffer> CreateUnique(uint32_t count, BufferAllocType allocType, const void* data = nullptr);
		static std::shared_ptr<IndexBuffer> CreateShared(uint32_t count, BufferAllocType allocType, const void* data = nullptr);
	private:
		virtual void SetRawData(const void* data, uint32_t size) const = 0;
	};

	template<size_t MAX_SIZE>
	inline void IndexBuffer::SetData(const std::array<uint32_t, MAX_SIZE>& data, uint32_t count)
	{
		SetRawData(data.data(), count * sizeof(uint32_t));
	}
}
