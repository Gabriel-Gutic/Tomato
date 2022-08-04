#include "pchTomato.h"
#include "Scene.h"


namespace Tomato
{
	Scene::Scene()
	{
		m_Camera = std::make_unique<Camera>();
	}

	Scene::~Scene()
	{
		for (auto& layer : m_LayerStack)
			delete layer;
	}

	std::unique_ptr<Camera>& Scene::GetCamera()
	{
		return m_Camera;
	}

	const std::unique_ptr<Camera>& Scene::GetCamera() const
	{
		return m_Camera;
	}

	std::vector<Layer*>& Scene::GetLayers()
	{
		return m_LayerStack;
	}

	const std::vector<Layer*>& Scene::GetLayers() const
	{
		return m_LayerStack;
	}

	void Scene::PushLayer(Layer* layer)
	{
		m_LayerStack.push_back(layer);
	}

	void Scene::PopLayer()
	{
		m_LayerStack.pop_back();
	}
}
