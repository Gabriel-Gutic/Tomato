#include "pchTomato.h"
#include "IndexBuffer.h"

#include <glad/glad.h>


namespace Tomato
{
	IndexBuffer::IndexBuffer(unsigned int mvn)
	{
		this->Bind();

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mvn * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void IndexBuffer::SetRawData(const unsigned int* data, unsigned int size) const
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
	}
}