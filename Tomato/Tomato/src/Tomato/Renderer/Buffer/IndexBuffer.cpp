#include "pchTomato.h"
#include "IndexBuffer.h"

#include <glad/glad.h>


namespace Tomato
{
	IndexBuffer::IndexBuffer(UInt mvn)
	{
		this->Bind();

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mvn * sizeof(UInt), nullptr, GL_DYNAMIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void IndexBuffer::SetRawData(const UInt* data, UInt size) const
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
	}
}