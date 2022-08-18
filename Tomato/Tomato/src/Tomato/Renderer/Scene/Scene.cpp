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

	std::shared_ptr<Object>& Scene::PushObject(std::string_view name, const std::shared_ptr<Object>& obj)
	{
		const char* c_name = name.data();
		TOMATO_ASSERT(m_Objects.find(c_name) == m_Objects.end(), "Object '{0}' already exist!", c_name);
		m_Objects[c_name] = obj;
		return m_Objects[c_name];
	}

	void Scene::PopObject(std::string_view name)
	{
		const char* c_name = name.data();
		TOMATO_ASSERT(m_Objects.find(c_name) != m_Objects.end(), "Object '{0}' doesn't exist!", c_name);
		m_Objects.erase(c_name);
	}

	bool Scene::Contains(std::string_view name) const
	{
		return m_Objects.find(name.data()) != m_Objects.end();
	}

	std::map<std::string, std::shared_ptr<Object>>& Scene::GetObjects()
	{
		return m_Objects;
	}

	const std::map<std::string, std::shared_ptr<Object>>& Scene::GetObjects() const
	{
		return m_Objects;
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
