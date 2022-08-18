#pragma once
#include "Renderer/Camera.h"
#include "Core/App/Layer.h"


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

		std::shared_ptr<Object>& PushObject(std::string_view name, const std::shared_ptr<Object>& obj);
		void PopObject(std::string_view name);
		template <typename T>
		std::shared_ptr<T> GetObject(std::string_view name);
		bool Contains(std::string_view name) const;
		
		std::map<std::string, std::shared_ptr<Object>>& GetObjects();
		const std::map<std::string, std::shared_ptr<Object>>& GetObjects() const;

		void PushLayer(Layer* layer);
		void PopLayer();
	private:
		std::vector<Layer*> m_LayerStack;
		std::unique_ptr<Camera> m_Camera;

		std::map<std::string, std::shared_ptr<Object>> m_Objects;
	};

	template <typename T>
	inline std::shared_ptr<T> Scene::GetObject(std::string_view name)
	{
		const char* c_name = name.data();
		TOMATO_ASSERT(m_Objects.find(c_name) != m_Objects.end(), "Object '{0}' doesn't exist!", c_name);
		auto ptr = std::dynamic_pointer_cast<T>(m_Objects[c_name]);
		TOMATO_ASSERT(ptr, "Dynamic pointer cast failed!");
		return ptr;
	}
}



