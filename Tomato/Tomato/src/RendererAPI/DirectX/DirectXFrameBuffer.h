#pragma once
#include "Tomato/Renderer/Buffer/FrameBuffer.h"


namespace Tomato
{
	class DirectXFrameBuffer : public FrameBuffer
	{
	public:
		DirectXFrameBuffer(uint32_t width = 1280, uint32_t height = 720);
		virtual ~DirectXFrameBuffer() override;

		std::any GetRenderTargetView() const;
	protected:
		std::any m_RenderTargetView;
	};
}
