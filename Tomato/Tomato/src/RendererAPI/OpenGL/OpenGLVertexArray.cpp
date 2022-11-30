#include "pchTomato.h"
#include "OpenGLVertexArray.h"

#include "Tomato/Renderer/Renderer.h"
#include "Tomato/Renderer/Line.h"

#include <glad/glad.h>


namespace Tomato
{
	OpenGLVertexArray::OpenGLVertexArray(const std::initializer_list<uint8_t>& layout)
	{
		glCreateVertexArrays(1, &m_RendererID);

		this->Bind();

		size_t size = 0, vertex_size = 0;

		for (const auto& el : layout)
		{
			ASSERT(el <= 4, "Invalid layout with component size {0}", el);
			vertex_size += el * sizeof(float);
		}

		size_t i = 0;
		for (const auto& el : layout)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, el, GL_FLOAT, GL_FALSE, vertex_size, (const void*)size);
			size += el * sizeof(float);
			i++;
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