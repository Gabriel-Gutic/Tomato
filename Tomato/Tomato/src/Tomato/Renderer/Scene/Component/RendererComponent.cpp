#include "pchTomato.h"
#include "RendererComponent.h"

namespace Tomato::Component
{
	Renderer::Renderer(std::string_view sprite, const Float4& color)
		:Sprite(sprite), Color(color)
	{

	}
}
