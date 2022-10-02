#pragma once
#include "Tomato/Renderer/Texture/Texture.h"


namespace Tomato
{
	class OpenGLTexture : public Texture
	{
	private:
		void Setup();
	public:
		OpenGLTexture(uint32_t width, uint32_t height, const uint8_t* data = nullptr, Image::Format format = Image::Format::RGB);
		OpenGLTexture(std::string_view path);
		virtual ~OpenGLTexture() override;

		void Bind() const;
		void BindUnit(unsigned int unit) const;

		unsigned int GetID() const;
	private:
		static int ConvertFormat(Image::Format format);
	private:
		unsigned int m_RendererID;
	};
}
