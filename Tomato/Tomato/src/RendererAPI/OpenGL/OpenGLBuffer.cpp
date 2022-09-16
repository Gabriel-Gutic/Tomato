#include "pchTomato.h"
#include "OpenGLBuffer.h"

#include "Tomato/Renderer/Buffer/Buffer.h"
#include <glad/glad.h>


namespace Tomato
{
	OpenGLBuffer::OpenGLBuffer()
		:m_RendererID(0)
	{
		glCreateBuffers(1, &m_RendererID);
	}

	OpenGLBuffer::~OpenGLBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	uint32_t OpenGLBuffer::AllocTypeConversion(BufferAllocType allocType)
	{
		switch (allocType)
		{
		case Tomato::BufferAllocType::Static:
			return GL_STATIC_DRAW;
		case Tomato::BufferAllocType::Dynamic:
			return GL_DYNAMIC_DRAW;
		}
		return 0;
	}
}

