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

		UInt GetID() const;
	private:
		UInt m_RendererID;
	};
}
