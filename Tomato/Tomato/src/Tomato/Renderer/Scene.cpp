#include "pchTomato.h"
#include "Scene.h"


namespace Tomato
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	std::unique_ptr<Camera>& Scene::GetCamera()
	{
		return m_Camera;
	}

	const std::unique_ptr<Camera>& Scene::GetCamera() const
	{
		return m_Camera;
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
