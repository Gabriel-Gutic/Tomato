#include "pchTomato.h"
#include "OpenGLRenderer3D.h"

#include <glad/glad.h>


namespace Tomato
{
	struct RendererData
	{
		static const uint32_t MaxVertexNumber = 1024;
	};

	OpenGLRenderer3D::OpenGLRenderer3D()
	{
		m_Shader = std::move(Shader::CreateUnique("assets/Shaders/VertexShader.glsl", "assets/Shaders/FragmentShader.glsl"));
		m_VertexBuffer = std::make_unique<VertexBuffer>(RendererData::MaxVertexNumber);
		m_VertexArray = std::make_unique<VertexArray>();

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	OpenGLRenderer3D::~OpenGLRenderer3D()
	{

	}
}