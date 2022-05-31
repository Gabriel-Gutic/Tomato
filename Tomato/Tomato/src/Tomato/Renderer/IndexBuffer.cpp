#include "pchTomato.h"
#include "IndexBuffer.h"

#include <glad/glad.h>


namespace Tomato
{
	IndexBuffer::IndexBuffer(std::initializer_list<UInt> indices)
	{
		this->Bind();

		m_Size = indices.size();

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Size * sizeof(UInt), indices.begin(), GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
	}

	UInt IndexBuffer::GetSize() const
	{
		return m_Size;
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

}