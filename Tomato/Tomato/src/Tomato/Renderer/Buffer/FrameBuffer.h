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

		UInt GetID() const;
		std::unique_ptr<Texture>& GetTexture();
		const std::unique_ptr<Texture>& GetTexture() const;

		std::pair<UInt, UInt> GetSize() const;
		void SetSize(UInt width, UInt height);
	private:
		UInt m_Width, m_Height;
		UInt m_RendererID;
		UInt m_RenderBuffer;
		std::unique_ptr<Texture> m_Texture;
	};
}
