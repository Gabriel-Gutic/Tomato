#pragma once


namespace Tomato
{
	class ShaderProgram
	{
	public:
		ShaderProgram(std::string_view vertexSource, std::string_view fragmentSource);
		~ShaderProgram();

		void Use(bool use = true);
	private:
		UInt m_RendererID;
	};
}