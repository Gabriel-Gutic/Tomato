#include "pchTomato.h"
#include "Shader.h"

#include "RendererAPI/OpenGL/OpenGLShader.h"
#include "RendererAPI/RendererAPI.h"


namespace Tomato
{
	std::unique_ptr<Shader> Shader::CreateUnique(std::string_view vertexSource, std::string_view fragmentSource)
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return std::make_unique<OpenGLShader>(vertexSource, fragmentSource);
		}
		return nullptr;
	}

	std::shared_ptr<Shader> Shader::CreateShared(std::string_view vertexSource, std::string_view fragmentSource)
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return std::make_shared<OpenGLShader>(vertexSource, fragmentSource);
		}
		return nullptr;
	}

	std::string Shader::TypeToString(ShaderType type)
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