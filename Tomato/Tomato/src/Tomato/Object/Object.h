#pragma once
#include "Component/Component.h"


namespace Tomato
{
	class Object
	{
	public:
		Object() = default;
		virtual ~Object() = default;

		virtual std::string ToString() const;

		template <typename T>
		T* Cast();
		template <typename T>
		static std::shared_ptr<T> Cast(const std::shared_ptr<Object>& obj);

		friend std::ostream& operator<<(std::ostream& os, const Object& obj);
		
		void AddComponent(const std::shared_ptr<Component>& comp);
		template <typename T>
		bool HasComponent() const;

		template <typename T>
		std::shared_ptr<T>& GetComponent();
		template <typename T>
		const std::shared_ptr<T>& GetComponent() const;
	protected:
		std::vector<std::shared_ptr<Component>> m_Components;
	};

	template<typename T>
	inline T* Object::Cast()
	{
		return dynamic_cast<T*>(this);
	}

	template<typename T>
	inline std::shared_ptr<T> Object::Cast(const std::shared_ptr<Object>& obj)
	{
		return std::dynamic_pointer_cast<T>(obj);
	}

	template <typename T>
	inline bool Object::HasComponent() const
	{
		for (const auto& comp : m_Components)
		{
			auto ptr = std::dynamic_pointer_cast<T>(comp);
			if (ptr)
				return true;
		}
		return false;
	}

	template <typename T>
	std::shared_ptr<T>& Object::GetComponent()
	{
		for (auto& comp : m_Components)
		{
			auto ptr = std::dynamic_pointer_cast<T>(comp);
			if (ptr)
				return ptr;
		}
		TOMATO_ASSERT(0, "Component not found!");
	}

	template <typename T>
	const std::shared_ptr<T>& Object::GetComponent() const
	{
		for (const auto& comp : m_Components)
		{
			auto ptr = std::dynamic_pointer_cast<T>(comp);
			if (ptr)
				return ptr;
		}

		return nullptr;
	}
}
