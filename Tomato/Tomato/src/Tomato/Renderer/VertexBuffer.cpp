#include "pchTomato.h"
#include "VertexBuffer.h"

#include <glad/glad.h>


namespace Tomato
{
	VertexBuffer::VertexBuffer(std::initializer_list<Vertex> list)
		:Buffer()
	{
		this->Bind();

		glBufferData(GL_ARRAY_BUFFER, list.size() * sizeof(Vertex), list.begin(), GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}
}


