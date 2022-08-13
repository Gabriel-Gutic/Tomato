#include "pchTomato.h"
#include "Shader.h"

#include "glad/glad.h"

#include "Shader.h"


namespace Tomato
{
	Shader::Shader(std::string_view vertexSource, std::string_view fragmentSource)
	{
		UInt vertexShader = CompileShader(vertexSource, ShaderType::Vertex);
		UInt fragmentShader = CompileShader(fragmentSource, ShaderType::Fragment);
	
		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);
		glLinkProgram(m_RendererID);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Use(bool use) const
	{
		if (use)
		{
			glUseProgram(m_RendererID);
		}
		else 
		{
			glUseProgram(0);
		}
	}

	void Shader::SetFloat(std::string_view location, Float value) const
	{
		Int id = GetUniformLocation(location);
		glUniform1f(id, value);
	}

	void Shader::SetFloat2(std::string_view location, const Float2& vec) const
	{
		Int id = GetUniformLocation(location);
		glUniform2f(id, vec.x, vec.y);
	}

	void Shader::SetFloat3(std::string_view location, const Float3& vec) const
	{
		Int id = GetUniformLocation(location);
		glUniform3f(id, vec.x, vec.y, vec.z);
	}

	void Shader::SetFloat4(std::string_view location, const Float4& vec) const
	{
		Int id = GetUniformLocation(location);
		glUniform4f(id, vec.x, vec.y, vec.z, vec.w);
	}

	void Shader::SetInt(std::string_view location, Int value) const
	{
		Int id = GetUniformLocation(location);
		glUniform1i(id, value);
	}

	void Shader::SetInt2(std::string_view location, const Int2& vec) const
	{
		Int id = GetUniformLocation(location);
		glUniform2i(id, vec.x, vec.y);
	}

	void Shader::SetInt3(std::string_view location, const Int3& vec) const
	{
		Int id = GetUniformLocation(location);
		glUniform3i(id, vec.x, vec.y, vec.z);
	}

	void Shader::SetInt4(std::string_view location, const Int4& vec) const
	{
		Int id = GetUniformLocation(location);
		glUniform4i(id, vec.x, vec.y, vec.z, vec.w);
	}

	void Shader::SetMat4(std::string_view location, const Mat4& matrix) const
	{
		Int id = GetUniformLocation(location);
		glUniformMatrix4fv(id, 1, GL_FALSE, matrix.GetData().data()->data());
	}

	void Shader::SetIntData(std::string_view location, UInt size, const int* data) const
	{
		Int id = GetUniformLocation(location);
		glUniform1iv(id, size, data);
	}

	UInt Shader::GetID() const
	{
		return m_RendererID;
	}

	Int Shader::GetUniformLocation(std::string_view uniform) const
	{
		this->Use();
		const char* c_uniform = uniform.data();
		if (m_UniformLocations.find(c_uniform) != m_UniformLocations.end())
			return m_UniformLocations[c_uniform];

		Int id = glGetUniformLocation(m_RendererID, c_uniform);
		//TOMATO_ASSERT(id != -1, "Uniform {0} not found!", c_uniform);

		return id;
	}

	UInt Shader::CompileShader(std::string_view source, ShaderType type)
	{
		auto result = File::Read(source);

		TOMATO_ASSERT(result.has_value(), "File '{0}' not found!", source.data());

		const char* shader_source = result.value().c_str();

		UInt id = glCreateShader(GLenum(type));
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