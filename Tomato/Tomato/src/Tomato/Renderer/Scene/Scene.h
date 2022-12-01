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
		Mat4 GetViewProjection(bool viewReversed = false) const;

		std::vector<Layer*>& GetLayers();
		const std::vector<Layer*>& GetLayers() const;

		std::shared_ptr<Entity>& PushEntity(const std::string& name, const std::shared_ptr<Entity>& entity);
		void PopEntity(const std::string& name);
		const std::shared_ptr<Entity>& GetEntity(const std::string& name);
		bool Contains(const std::string& name) const;
		
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



