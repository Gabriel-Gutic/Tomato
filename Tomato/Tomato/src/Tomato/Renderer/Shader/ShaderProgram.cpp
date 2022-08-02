#include "pchTomato.h"
#include "ShaderProgram.h"

#include "glad/glad.h"

#include "Shader.h"


namespace Tomato
{
	ShaderProgram::ShaderProgram(std::string_view vertexSource, std::string_view fragmentSource)
	{
		Shader* vertexShader = new Shader(vertexSource, ShaderType::Vertex);
		Shader* fragmentShader = new Shader(fragmentSource, ShaderType::Fragment);
	
		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertexShader->GetID());
		glAttachShader(m_RendererID, fragmentShader->GetID());
		glLinkProgram(m_RendererID);

		delete vertexShader;
		delete fragmentShader;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_RendererID);
	}

	void ShaderProgram::Use(bool use)
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

	void ShaderProgram::SetUniformMat4(std::string_view location, const Mat4& matrix)
	{
		Int id = glGetUniformLocation(m_RendererID, location.data());
		TOMATO_ASSERT(id != -1, "Uniform {0} not found!", location.data());
		glUniformMatrix4fv(id, 1, GL_FALSE, &matrix[0][0]);
	}

	UInt ShaderProgram::GetID() const
	{
		return m_RendererID;
	}
}