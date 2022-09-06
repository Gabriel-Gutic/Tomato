#include "pchTomato.h"
#include "VertexBuffer.h"

#include <glad/glad.h>


namespace Tomato
{
	VertexBuffer::VertexBuffer(unsigned int mvn)
		:Buffer()
	{
		this->Bind();

		glBufferData(GL_ARRAY_BUFFER, mvn * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::SetRawData(const Vertex* data, unsigned int size) const
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, (const float*)(data));
	}
}


