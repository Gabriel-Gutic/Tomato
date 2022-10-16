#pragma once
#include "Tomato/Renderer/Buffer/FrameBuffer.h"


namespace Tomato
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(uint32_t width = 1280, uint32_t height = 720);
		virtual ~OpenGLFrameBuffer() override;

		uint32_t GetID() const;

		void Bind() const;
		void Unbind() const;

		virtual void SetSize(uint32_t width, uint32_t height) override;
	protected:
		uint32_t m_RendererID;
		uint32_t m_RenderBuffer;
	};
}