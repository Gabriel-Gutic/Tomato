#pragma once


namespace Tomato
{
	enum class ShaderType
	{
		Vertex = 0x8B31,
		Fragment = 0x8B30,
	};

	class Shader
	{
	public:
		Shader(std::string_view source, ShaderType type);
		~Shader();

		UInt GetID() const;
		ShaderType GetType() const;
	private:
		static const char* TypeToString(ShaderType type);
	private:
		UInt m_RendererID;
		ShaderType m_Type;
	};
}
