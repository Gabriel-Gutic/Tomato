#pragma once


namespace Tomato
{
	class Object
	{
	public:
		Object() = default;
		virtual ~Object() = default;

		virtual std::string ToString() const;

		template <typename T>
		std::shared_ptr<T> Cast();

		friend std::ostream& operator<<(std::ostream& os, const Object& obj);
	};

	template<typename T>
	inline std::shared_ptr<T> Object::Cast()
	{
		return std::shared_ptr<T>(this);
	}
}
