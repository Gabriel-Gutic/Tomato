#pragma once
#include "Renderer/Texture/Texture.h"


namespace Tomato
{
	class FrameBuffer
	{
	public:
		FrameBuffer(uint32_t width = 1280, uint32_t height = 720);
		virtual ~FrameBuffer() = default;

		const std::shared_ptr<Texture>& GetTexture() const;

		virtual UInt2 GetSize() const;
		virtual void SetSize(uint32_t width, uint32_t height);

		static std::shared_ptr<FrameBuffer> CreateShared();
		static std::unique_ptr<FrameBuffer> CreateUnique();
	protected:
		uint32_t m_Width, m_Height;
		std::shared_ptr<Texture> m_Texture;
	};
}
