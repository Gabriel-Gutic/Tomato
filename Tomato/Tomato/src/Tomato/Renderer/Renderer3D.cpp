#include "pchTomato.h"
#include "Renderer3D.h"

#include "RendererAPI/RendererAPI.h"
#include "RendererAPI/OpenGL/OpenGLRenderer3D.h"


namespace Tomato
{
	Renderer3D* Renderer3D::s_Instance = nullptr;
	void Renderer3D::Initialize()
	{
		TOMATO_ASSERT(!s_Instance, "Renderer3D already initialized!");
		switch (RendererAPI::GetType())
		{
		case RendererType::OpenGL:
			s_Instance = new OpenGLRenderer3D();
		}
		TOMATO_ASSERT(s_Instance, "Failed to initialize Renderer3D!");
	}

	void Renderer3D::Terminate()
	{
		delete s_Instance;
	}

	Renderer3D* Renderer3D::Get()
	{
		return s_Instance;
	}
}
