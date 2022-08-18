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
		T* Cast();
		template <typename T>
		static std::shared_ptr<T> Cast(const std::shared_ptr<Object>& obj);

		friend std::ostream& operator<<(std::ostream& os, const Object& obj);
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
}
