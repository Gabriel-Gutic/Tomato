#pragma once
#include "Shader.h"
#include "Buffer/VertexArray.h"
#include "Buffer/VertexBuffer.h"
#include "Buffer/FrameBuffer.h"
#include "Texture/Texture.h"
#include "Texture/Tilemap.h"
#include "Scene/Entity.h"
#include "Texture/Font.h"


namespace Tomato
{
	enum class RendererType
	{
		_2D,
		_3D,
	};

	class Renderer
	{
		Renderer() = default;
	public:
		Renderer(const Renderer&) = delete;

		static RendererType GetType();
	private:
		static RendererType s_Type;
	};

	
}

