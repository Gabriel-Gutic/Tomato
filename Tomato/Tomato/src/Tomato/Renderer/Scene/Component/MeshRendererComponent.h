#pragma once
#include "Renderer/Mesh.h"


namespace Tomato
{
	struct MeshRendererComponent
	{
		std::string Sprite;
		Float4 Color;
		Mesh mesh;

		MeshRendererComponent(std::string_view sprite = "None", const Float4& color = Float4(1.0f, 1.0f, 1.0f, 1.0f), const Mesh& mesh = Mesh());
		MeshRendererComponent(const MeshRendererComponent&) = default;
		~MeshRendererComponent() = default;

		void ToImGui();
	};
}