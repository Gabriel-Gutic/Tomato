#include "pchTomato.h"
#include "VertexArray.h"

#include <glad/glad.h>

#include "Vertex.h"


namespace Tomato
{
	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);

		this->Bind();

		size_t size = 0;

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)size);
		size += sizeof(Float3);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)size);
		size += sizeof(Float4);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)size);
		size += sizeof(float);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)size);
		size += sizeof(Float2);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)size);
		size += sizeof(float);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

}