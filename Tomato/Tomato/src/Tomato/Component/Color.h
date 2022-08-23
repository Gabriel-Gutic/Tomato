#pragma once


namespace Tomato
{
	struct Color
	{
	public:
		union
		{
			Float4 rgba;
			struct {
				Float3 rgb;
			};
			struct {
				Float Red;
				Float Green;
				Float Blue;
				Float Alpha;
			};
			struct {
				Float r;
				Float g;
				Float b;
				Float a;
			};
		};

		Color(Float r = 1.0f, Float g = 1.0f, Float b = 1.0f, Float a = 1.0f);
		Color(const Float3& rgb);
		Color(const Float4& rgba);
		Color(const Color& other);
		~Color() = default;

		Color& operator=(const Color& other);

		void ToImGui();

		Float* ToPtr();
	};
}
