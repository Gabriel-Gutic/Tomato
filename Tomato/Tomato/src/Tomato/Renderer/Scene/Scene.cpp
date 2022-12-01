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
		while (!m_LayerStack.empty())
			PopLayer();
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

	const std::shared_ptr<Entity>& Scene::GetEntity(const std::string& name)
	{
		TOMATO_ASSERT(m_Entities.find(name) != m_Entities.end(), "Entity '{0}' doesn't exist!", name);
		return m_Entities[name];
	}

	std::shared_ptr<Entity>& Scene::PushEntity(const std::string& name, const std::shared_ptr<Entity>& entity)
	{
		entity->AddComponent<MeshRendererComponent>();
		entity->AddComponent<TransformComponent>();
		TOMATO_ASSERT(m_Entities.find(name) == m_Entities.end(), "Entity '{0}' already exist!", name);
		m_Entities[name] = entity;
		return m_Entities[name];
	}

	void Scene::PopEntity(const std::string& name)
	{
		TOMATO_ASSERT(m_Entities.find(name) != m_Entities.end(), "Entity '{0}' doesn't exist!", name);
		m_Entities.erase(name);
	}

	bool Scene::Contains(const std::string& name) const
	{
		return m_Entities.find(name) != m_Entities.end();
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
		delete m_LayerStack.back();
		m_LayerStack.pop_back();
	}
}
