#pragma once
#include "Renderer/Camera.h"
#include "Core/App/Layer.h"
#include "Entity.h"


namespace Tomato
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		const std::unique_ptr<Camera>& GetCamera() const;

		std::vector<Layer*>& GetLayers();
		const std::vector<Layer*>& GetLayers() const;

		std::shared_ptr<Entity>& PushEntity(std::string_view name, const std::shared_ptr<Entity>& entity);
		void PopEntity(std::string_view name);
		template <typename T>
		std::shared_ptr<T> GetEntity(std::string_view name);
		bool Contains(std::string_view name) const;
		
		std::map<std::string, std::shared_ptr<Entity>>& GetEntities();
		const std::map<std::string, std::shared_ptr<Entity>>& GetEntities() const;

		void PushLayer(Layer* layer);
		void PopLayer();
	private:
		std::vector<Layer*> m_LayerStack;
		std::unique_ptr<Camera> m_Camera;

		std::map<std::string, std::shared_ptr<Entity>> m_Entities;
	};

	template <typename T>
	std::shared_ptr<T> Scene::GetEntity(std::string_view name)
	{
		const char* c_name = name.data();
		TOMATO_ASSERT(m_Entities.find(c_name) != m_Entities.end(), "Entity '{0}' doesn't exist!", c_name);
		auto ptr = std::dynamic_pointer_cast<T>(m_Entities[c_name]);
		TOMATO_ASSERT(ptr, "Dynamic pointer cast failed!");
		return ptr;
	}
}



