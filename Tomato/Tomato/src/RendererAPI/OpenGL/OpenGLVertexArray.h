#pragma once
#include "Tomato/Renderer/Buffer/VertexArray.h"


namespace Tomato
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray(const std::initializer_list<uint8_t>& layout = {});
		virtual ~OpenGLVertexArray() override;

		virtual void Bind() override;
		virtual void Unbind() override;
	private:
		uint32_t m_RendererID;
	};
}
