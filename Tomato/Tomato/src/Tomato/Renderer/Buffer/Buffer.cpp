#include "pchTomato.h"
#include "Buffer.h"

#include <glad/glad.h>


namespace Tomato
{
	Buffer::Buffer()
	{
		glCreateBuffers(1, &m_RendererID);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &m_RendererID);
		PRINT("BUFFER DELETED");
	}
}


