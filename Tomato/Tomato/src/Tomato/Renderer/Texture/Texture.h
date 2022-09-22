#pragma once
#include "Image.h"


namespace Tomato
{
	class Texture
	{
		void Setup();
	public:
		Texture(unsigned int width, unsigned int height, unsigned char* data, Image::Format format);
		Texture(unsigned int width, unsigned int height);
		Texture(std::string_view path);
		~Texture();

		void Bind() const;
		void BindUnit(unsigned int unit) const;

		void Reset(unsigned int width, unsigned int height);
		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

		unsigned int GetID() const;

		static std::shared_ptr<Texture> Create(std::string_view path);
	private:
		static int ConvertFormat(Image::Format format);
	private:
		unsigned int m_RendererID;
		unsigned int m_Width, m_Height;
	};
}
