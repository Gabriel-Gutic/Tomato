#pragma once
#include "Core/App/UUID.h"


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
		entt::basic_registry<uint64_t> m_Buffer;
	
		static Registry* s_Instance;
	};

	template<typename T>
	inline T& Registry::Add(const UUID& uuid)
	{
		return m_Buffer.get_or_emplace<T>(uuid.Get());
	}

	template<typename T, class ...Args>
	inline T& Registry::Add(const UUID& uuid, Args && ...args)
	{
		return m_Buffer.get_or_emplace<T>(uuid.Get(), args);
	}

	template<typename T>
	inline bool Registry::Has(const UUID& uuid) const
	{
		return m_Buffer.all_of<T>(uuid.Get());
	}

	template<typename T>
	inline T& Registry::Get(const UUID& uuid)
	{
		if (Has<T>(uuid))
			return m_Buffer.get_or_emplace<T>(uuid.Get());
		TOMATO_ASSERT(0, "Component doesn't exit!");
		return Add<T>(uuid);
	}
}
