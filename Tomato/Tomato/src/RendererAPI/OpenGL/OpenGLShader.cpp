#include "pchTomato.h"
#include "OpenGLShader.h"

#include <glad/glad.h>


namespace Tomato
{
	OpenGLShader::OpenGLShader(std::string_view vertexSource, std::string_view fragmentSource)
	{
		unsigned int vertexShader = CompileShader(vertexSource, ShaderType::Vertex);
		unsigned int fragmentShader = CompileShader(fragmentSource, ShaderType::Fragment);

		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);
		glLinkProgram(m_RendererID);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Use()
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::SetMat4(std::string_view location, const Mat4& matrix)
	{
		int id = GetUniformLocation(location);
		glUniformMatrix4fv(id, 1, GL_FALSE, matrix.GetData().data()->data());
	}

	void OpenGLShader::SetIntData(std::string_view location, unsigned int size, const int* data)
	{
		int id = GetUniformLocation(location);
		glUniform1iv(id, size, data);
	}

	unsigned int OpenGLShader::GetID() const
	{
		return m_RendererID;
	}

	int OpenGLShader::GetUniformLocation(std::string_view uniform) const
	{
		glUseProgram(m_RendererID);
		const char* c_uniform = uniform.data();
		if (m_UniformLocations.find(c_uniform) != m_UniformLocations.end())
			return m_UniformLocations[c_uniform];

		int id = glGetUniformLocation(m_RendererID, c_uniform);
		if (id == -1)
			TOMATO_ERROR("Uniform {0} not found!", c_uniform);

		return id;
	}

	unsigned int OpenGLShader::CompileShader(std::string_view source, ShaderType type)
	{
		auto result = File::Read(source);

		TOMATO_ASSERT(result.has_value(), "File '{0}' not found!", source.data());

		const char* shader_source = result.value().c_str();

		unsigned int id = glCreateShader(GLenum(type));
		glShaderSource(id, 1, &shader_source, nullptr);
		glCompileShader(id);

		int succes;
		const unsigned short bufferSize = 512;
		char buffer[bufferSize];

		glGetShaderiv(id, GL_COMPILE_STATUS, &succes);

		if (!succes)
		{
			glGetShaderInfoLog(id, bufferSize, NULL, buffer);
			TOMATO_ASSERT(0, "{1} Shader Syntax Error: {0}", buffer, TypeToString(type));
		}

		return id;
	}
}