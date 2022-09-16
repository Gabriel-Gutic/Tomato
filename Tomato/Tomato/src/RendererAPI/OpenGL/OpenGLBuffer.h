#pragma once
#include "Tomato/Renderer/Buffer/Buffer.h"


namespace Tomato
{
	class OpenGLBuffer
	{
	public:
		OpenGLBuffer();
		virtual ~OpenGLBuffer();

		static uint32_t AllocTypeConversion(BufferAllocType allocType);
	protected:
		uint32_t m_RendererID;
	};
}
