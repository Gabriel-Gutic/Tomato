#pragma once
#include "Renderer/Texture/Texture.h"


namespace Tomato
{
	class FrameBuffer
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		void Bind() const;
		void Unbind() const;

		unsigned int GetID() const;
		const std::shared_ptr<Texture>& GetTexture() const;

		std::pair<unsigned int, unsigned int> GetSize() const;
		void SetSize(unsigned int width, unsigned int height);
	private:
		unsigned int m_Width, m_Height;
		unsigned int m_RendererID;
		unsigned int m_RenderBuffer;
		std::shared_ptr<Texture> m_Texture;
	};
}
