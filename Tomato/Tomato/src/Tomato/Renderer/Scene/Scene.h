#pragma once
#include "Core/App/Layer.h"
#include "Entity.h"


namespace Tomato
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		const std::unique_ptr<Entity>& GetCamera() const;

		std::vector<Layer*>& GetLayers();
		const std::vector<Layer*>& GetLayers() const;

		std::shared_ptr<Entity>& PushEntity(std::string_view name, const std::shared_ptr<Entity>& entity);
		void PopEntity(std::string_view name);
		std::shared_ptr<Entity> GetEntity(std::string_view name);
		bool Contains(std::string_view name) const;
		
		std::map<std::string, std::shared_ptr<Entity>>& GetEntities();
		const std::map<std::string, std::shared_ptr<Entity>>& GetEntities() const;

		void PushLayer(Layer* layer);
		void PopLayer();
	private:
		std::vector<Layer*> m_LayerStack;
		std::unique_ptr<Entity> m_Camera;

		std::map<std::string, std::shared_ptr<Entity>> m_Entities;
	};
}



