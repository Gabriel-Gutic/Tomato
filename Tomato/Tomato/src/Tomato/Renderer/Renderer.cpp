#include "pchTomato.h"
#include "Renderer.h"

#include "App.h"


namespace Tomato
{
	Renderer* Renderer::s_Instance = nullptr;
	void Renderer::Initialize()
	{
		TOMATO_ASSERT(!s_Instance, "Renderer already initialized!");

		s_Instance = new Renderer();

		s_Instance->m_ShaderProgram = std::make_unique<ShaderProgram>("assets/Shaders/VertexShader.glsl", "assets/Shaders/FragmentShader.glsl");
	}

	void Renderer::Terminate()
	{
		delete s_Instance;
	}

	void Renderer::Begin()
	{
		s_Instance->m_ShaderProgram->Use();

		auto view = App::GetCamera()->Update();

		s_Instance->m_ShaderProgram->SetUniformMat4("View", view);
	}

	void Renderer::End()
	{
		s_Instance->m_ShaderProgram->Use(false);
	}

	Renderer* Renderer::Get()
	{
		return s_Instance;
	}
}
