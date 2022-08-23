#include "pchTomato.h"
#include "Scene.h"

#include "Component/Transform.h"
#include "Component/Color.h"


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

	std::shared_ptr<Entity>& Scene::PushEntity(std::string_view name, const std::shared_ptr<Entity>& entity)
	{
		entity->AddComponent<Transform>();
		entity->AddComponent<Color>();
		const char* c_name = name.data();
		TOMATO_ASSERT(m_Entities.find(c_name) == m_Entities.end(), "Entity '{0}' already exist!", c_name);
		m_Entities[c_name] = entity;
		return m_Entities[c_name];
	}

	void Scene::PopEntity(std::string_view name)
	{
		const char* c_name = name.data();
		TOMATO_ASSERT(m_Entities.find(c_name) != m_Entities.end(), "Entity '{0}' doesn't exist!", c_name);
		m_Entities.erase(c_name);
	}

	bool Scene::Contains(std::string_view name) const
	{
		return m_Entities.find(name.data()) != m_Entities.end();
	}

	std::map<std::string, std::shared_ptr<Entity>>& Scene::GetEntities()
	{
		return m_Entities;
	}

	const std::map<std::string, std::shared_ptr<Entity>>& Scene::GetEntities() const
	{
		return m_Entities;
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
