#include "pchTomato.h"
#include "Shader.h"

#include "Core/FileManager/File.h"

#include "glad/glad.h"


namespace Tomato
{
	Shader::Shader(std::string_view source, ShaderType type)
		:m_RendererID(0), m_Type(type)
	{
		auto result = File::Read(source);

		TOMATO_ASSERT(result.has_value(), "File '{0}' not found!", source.data());

		const char* shader_source = result.value().c_str();

		m_RendererID = glCreateShader(GLenum(type));
		glShaderSource(m_RendererID, 1, &shader_source, NULL);
		glCompileShader(m_RendererID);

		int succes;
		const unsigned short bufferSize = 512;
		char buffer[bufferSize];

		glGetShaderiv(m_RendererID, GL_COMPILE_STATUS, &succes);

		if (!succes)
		{
			glGetShaderInfoLog(m_RendererID, bufferSize, NULL, buffer);
			TOMATO_ASSERT(0, "{1} Shader Syntax Error: {0}", buffer, TypeToString(type));
		}
	}

	Shader::~Shader()
	{
		glDeleteShader(m_RendererID);
	}

	UInt Shader::GetID() const
	{
		return m_RendererID;
	}

	ShaderType Shader::GetType() const
	{
		return m_Type;
	}

	const char* Shader::TypeToString(ShaderType type)
	{
		switch (type)
		{
		case Tomato::ShaderType::Vertex:
			return "Vertex";
		case Tomato::ShaderType::Fragment:
			return "Fragment";
		}
		return "";
	}
}