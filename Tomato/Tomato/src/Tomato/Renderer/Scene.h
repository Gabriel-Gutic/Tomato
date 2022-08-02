#pragma once
#include "Camera.h"
#include "Layer.h"


namespace Tomato
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		std::unique_ptr<Camera>& GetCamera();
		const std::unique_ptr<Camera>& GetCamera() const;

		void PushLayer(Layer* layer);
		void PopLayer();
	private:
		std::vector<Layer*> m_LayerStack;
		std::unique_ptr<Camera> m_Camera;
	};
}



