#include "pchTomato.h"
#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>


namespace Tomato
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t count, BufferAllocType allocType, const void* data)
		:IndexBuffer(allocType), OpenGLBuffer()
	{
		this->Bind();

		uint32_t _allocType = OpenGLBuffer::AllocTypeConversion(allocType);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, _allocType);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::SetRawData(const void* data, uint32_t size) const
	{
		if (m_AllocType == BufferAllocType::Dynamic)
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
	}
}