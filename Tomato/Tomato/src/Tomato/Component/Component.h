#pragma once


namespace Tomato
{
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		virtual void ToImGui() = 0;
		virtual std::string GetType() const = 0;
	};
}
