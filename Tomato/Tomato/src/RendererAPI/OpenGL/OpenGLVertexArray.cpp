#include "pchTomato.h"
#include "OpenGLVertexArray.h"

#include "Tomato/Renderer/Renderer.h"

#include <glad/glad.h>


namespace Tomato
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);

		this->Bind();

		size_t size = 0;

		if (Renderer::GetType() == RendererType::_2D)
		{
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
		else
		{
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (const void*)size);
			size += sizeof(Float3);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (const void*)size);
			size += sizeof(Float4);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (const void*)size);
			size += sizeof(Float3);
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (const void*)size);
			size += sizeof(Float2);
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (const void*)size);
			size += sizeof(float);
		}
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}
}