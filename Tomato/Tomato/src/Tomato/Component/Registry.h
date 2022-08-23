#pragma once
#include "Core/App/UUID.h"

#include <entt/entt.hpp>


namespace Tomato
{
	class Registry
	{
		Registry() = default;
	public:
		Registry(const Registry&) = delete;
		~Registry() = default;

		static void Initialize();
		static void Terminate();

		template <typename T>
		T& Add(const UUID& uuid);
		template <typename T, class... Args>
		T& Add(const UUID& uuid, Args&& ...args);
		template <typename T>
		bool Has(const UUID& uuid) const;
		template <typename T>
		T& Get(const UUID& uuid);

		static Registry* Get();
	private:
		entt::registry m_Buffer;
	
		static Registry* s_Instance;
	};

	template<typename T>
	inline T& Registry::Add(const UUID& uuid)
	{
		TOMATO_BENCHMARKING_FUNCTION();
		m_Buffer.emplace<T>(static_cast<entt::entity>(uuid.Get()));
		return m_Buffer.get<T>(static_cast<entt::entity>(uuid.Get()));
	}

	template<typename T, class ...Args>
	inline T& Registry::Add(const UUID& uuid, Args && ...args)
	{
		TOMATO_BENCHMARKING_FUNCTION();
		if (!Has<T>(static_cast<entt::entity>(uuid.Get())))
			m_Buffer.emplace<T>(static_cast<entt::entity>(uuid.Get()), args);
		return m_Buffer.get<T>(static_cast<entt::entity>(uuid.Get()));
	}

	template<typename T>
	inline bool Registry::Has(const UUID& uuid) const
	{
		return m_Buffer.all_of<T>(static_cast<entt::entity>(uuid.Get()));
	}

	template<typename T>
	inline T& Registry::Get(const UUID& uuid)
	{
		TOMATO_BENCHMARKING_FUNCTION();
		if (Has<T>(uuid))
			return m_Buffer.get<T>(static_cast<entt::entity>(uuid.Get()));
		TOMATO_ASSERT(0, "Component doesn't exit!");
	}
}
