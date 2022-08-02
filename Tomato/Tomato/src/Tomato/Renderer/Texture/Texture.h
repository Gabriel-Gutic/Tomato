#pragma once


namespace Tomato
{
	class Texture
	{
	public:
		Texture(std::string_view path);
		~Texture();

		void Bind();
	private:
		UInt m_RendererID;
	};
}
