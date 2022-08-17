#pragma once


namespace Tomato
{
	class Object
	{
	public:
		Object() = default;
		virtual ~Object() = default;

		template <typename T>
		std::shared_ptr<T> Cast();
	};

	template<typename T>
	inline std::shared_ptr<T> Object::Cast()
	{
		return std::shared_ptr<T>(this);
	}
}
