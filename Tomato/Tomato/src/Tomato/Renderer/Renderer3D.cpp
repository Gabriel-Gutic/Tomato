#include "pchTomato.h"
#include "Renderer3D.h"

#include "RendererAPI/RendererAPI.h"
#include "RendererAPI/OpenGL/OpenGLRenderer3D.h"
#include "RendererAPI/DirectX/DirectXRenderer3D.h"


namespace Tomato
{
	Renderer3D* Renderer3D::s_Instance = nullptr;
	void Renderer3D::Initialize()
	{
		TOMATO_ASSERT(!s_Instance, "Renderer3D already initialized!");
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			s_Instance = new OpenGLRenderer3D();
			break;
		case RendererAPI::Type::DirectX:
			s_Instance = new DirectXRenderer3D();
			break;
		}
		TOMATO_ASSERT(s_Instance, "Failed to initialize Renderer3D!");
	}

	void Renderer3D::Terminate()
	{
		delete s_Instance;
	}

	void Renderer3D::Clear(const Float4& color) const
	{
		this->Clear(color.x, color.y, color.z, color.w);
	}

	Renderer3D* Renderer3D::Get()
	{
		return s_Instance;
	}
}
