#include "pchTomato.h"
#include "Buffer.h"


namespace Tomato
{
	Buffer::Buffer(BufferAllocType allocType)
		:m_AllocType(allocType)
	{
	}

	void Buffer::SetAllocType(BufferAllocType allocType)
	{
		m_AllocType = allocType;
	}
}


