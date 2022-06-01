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

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)sizeof(Float3));
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