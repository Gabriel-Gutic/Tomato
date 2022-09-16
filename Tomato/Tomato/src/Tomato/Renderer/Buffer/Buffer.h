#pragma once


namespace Tomato
{
	enum class BufferAllocType
	{
		Static = 0,
		Dynamic = 1,
	};

	class Buffer
	{
	public:
		Buffer(BufferAllocType allocType);
		virtual ~Buffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind(){};

		virtual void SetAllocType(BufferAllocType allocType);
	protected:
		BufferAllocType m_AllocType;
	};
}