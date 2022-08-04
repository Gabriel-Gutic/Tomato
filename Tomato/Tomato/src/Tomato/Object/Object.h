#pragma once


namespace Tomato
{
	class Object
	{
	public:
		Object() {}
		Object(std::string_view name);
		virtual ~Object(){}

		void SetName(std::string_view name);
		const std::string& GetName() const;
	protected:
		std::string m_Name;
	};
}
