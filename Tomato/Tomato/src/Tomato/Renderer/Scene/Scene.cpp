#include "pchTomato.h"
#include "Scene.h"

#include "Component/Component.h"
#include "Core/App/App.h"


namespace Tomato
{
	Scene::Scene()
	{
		m_Camera = std::make_unique<Entity>();
		m_Camera->AddComponent<CameraComponent>();
		auto& tran = m_Camera->AddComponent<TransformComponent>();
		tran.Position.z += 3;
	}

	Scene::~Scene()
	{
		for (auto& layer : m_LayerStack)
			delete layer;
	}

	const std::unique_ptr<Entity>& Scene::GetCamera() const
	{
		return m_Camera;
	}

	Mat4 Scene::GetViewProjection(bool viewReversed) const
	{
		if (!m_Camera->HasComponent<CameraComponent>() || !m_Camera->HasComponent<TransformComponent>())
			return Mat4(1.0f);
		auto& camera = m_Camera->GetComponent<CameraComponent>();
		auto& tran = m_Camera->GetComponent<TransformComponent>();

		return camera.GetView(tran, viewReversed) * camera.GetProjection();
	}

	std::vector<Layer*>& Scene::GetLayers()
	{
		return m_LayerStack;
	}

	const std::vector<Layer*>& Scene::GetLayers() const
	{
		return m_LayerStack;
	}

	std::shared_ptr<Entity> Scene::GetEntity(std::string_view name)
	{
		const char* c_name = name.data();
		TOMATO_ASSERT(m_Entities.find(c_name) != m_Entities.end(), "Entity '{0}' doesn't exist!", c_name);
		return m_Entities[c_name];
	}

	std::shared_ptr<Entity>& Scene::PushEntity(std::string_view name, const std::shared_ptr<Entity>& entity)
	{
		entity->AddComponent<RendererComponent>();
		entity->AddComponent<TransformComponent>();
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
