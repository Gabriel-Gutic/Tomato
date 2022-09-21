#include "pchTomato.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>


namespace Tomato
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size, BufferAllocType allocType, const void* data)
		:VertexBuffer(allocType), OpenGLBuffer()
	{
		this->Bind();

		uint32_t _allocType = OpenGLBuffer::AllocTypeConversion(allocType);

		glBufferData(GL_ARRAY_BUFFER, size, data, _allocType);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::SetRawData(const void* data, unsigned int size) const
	{
		if (m_AllocType == BufferAllocType::Dynamic)
			glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
}