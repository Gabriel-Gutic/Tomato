#pragma once


namespace Tomato
{
	class Texture
	{
		void Setup();
	public:
		Texture(UInt width, UInt height);
		Texture(std::string_view path);
		~Texture();

		void Bind() const;
		void BindUnit(UInt unit) const;

		void Reset(UInt width, UInt height);
		UInt GetWidth() const;
		UInt GetHeight() const;

		UInt GetID() const;

		static std::shared_ptr<Texture> Create(std::string_view path);
	private:
		UInt m_RendererID;
		UInt m_Width, m_Height;
	};
}
