#include "pchTomato.h"
#include "FrameBuffer.h"

#include <glad/glad.h>


namespace Tomato
{
	FrameBuffer::FrameBuffer()
		:m_Width(800), m_Height(800)
	{
		glGenFramebuffers(1, &m_RendererID);
		Bind();

		m_Texture = std::make_unique<Texture>(m_Width, m_Height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture->GetID(), 0);
	
		glGenRenderbuffers(1, &m_RenderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);
	
		TOMATO_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
		Unbind();
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
	}

	void FrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	}

	void FrameBuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	unsigned int FrameBuffer::GetID() const
	{
		return m_RendererID;
	}

	std::unique_ptr<Texture>& FrameBuffer::GetTexture()
	{
		return m_Texture;
	}

	const std::unique_ptr<Texture>& FrameBuffer::GetTexture() const
	{
		return m_Texture;
	}

	std::pair<unsigned int, unsigned int> FrameBuffer::GetSize() const
	{
		return { m_Width, m_Height };
	}

	void FrameBuffer::SetSize(unsigned int width, unsigned int height)
	{
		m_Width = width;
		m_Height = height;
		Bind();

		glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		m_Texture->Reset(width, height);
		Unbind();
	}


}