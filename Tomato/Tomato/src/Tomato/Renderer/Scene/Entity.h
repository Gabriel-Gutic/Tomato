#pragma once
#include "Core/App/Object.h"
#include "Core/App/UUID.h"

#include "Registry.h"


namespace Tomato
{
	class Entity : public Object
	{
	public:
		Entity() = default;
		Entity(const Entity&) = default;
		~Entity() = default;

		virtual std::string ToString() const override;

		const UUID& GetUUID() const;

		template <typename T>
		bool HasComponent() const;
		template <typename T, class... Args>
		T& AddComponent(Args&& ... args) const;
		template <typename T>
		T& GetComponent();
		template <typename T>
		const T& GetComponent() const;
	private:
		UUID m_UUID;
	};

	template<typename T>
	inline bool Entity::HasComponent() const
	{
		return Registry::Get()->Has<T>(m_UUID);
	}

	template<typename T, class ... Args>
	inline T& Entity::AddComponent(Args&& ... args) const
	{
		return  Registry::Get()->Add<T>(m_UUID, std::forward<Args>(args)...);
	}

	template<typename T>
	inline T& Entity::GetComponent()
	{
		return Registry::Get()->Get<T>(m_UUID);
	}

	template<typename T>
	inline const T& Entity::GetComponent() const
	{
		return Registry::Get()->Get<T>(m_UUID);
	}
}
