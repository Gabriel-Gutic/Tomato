#pragma once


namespace Tomato
{
	class ShaderProgram
	{
	public:
		ShaderProgram(std::string_view vertexSource, std::string_view fragmentSource);
		~ShaderProgram();

		void Use(bool use = true);

		UInt GetID() const;
	private:
		UInt m_RendererID;
	};
}