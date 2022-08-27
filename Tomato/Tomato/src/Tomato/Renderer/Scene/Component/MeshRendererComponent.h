#pragma once
#include "Renderer/Mesh.h"


namespace Tomato
{
	struct MeshRendererComponent
	{
		std::string Sprite;
		Float4 Color;
		Mesh Mesh;

		MeshRendererComponent(std::string_view sprite = "None", const Float4& color = Float4(1.0f, 1.0f, 1.0f, 1.0f));
		MeshRendererComponent(const MeshRendererComponent&) = default;
		~MeshRendererComponent() = default;

		void ToImGui();
	};
}