#pragma once


namespace Tomato
{
	class ShaderProgram
	{
	public:
		ShaderProgram(std::string_view vertexSource, std::string_view fragmentSource);
		~ShaderProgram();

		void Use(bool use = true);

		void SetUniformMat4(std::string_view location, const Mat4& matrix);

		UInt GetID() const;
	private:
		UInt m_RendererID;
	};
}