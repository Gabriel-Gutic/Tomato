#pragma once


namespace Tomato
{
	class Color
	{
	private:
		Color() = default;
	public:
		Color(const Color&) = delete;

		static const Float3 White;
		static const Float3 Black;
		static const Float3 Red;
		static const Float3 Green;
		static const Float3 Blue;
	};
}
