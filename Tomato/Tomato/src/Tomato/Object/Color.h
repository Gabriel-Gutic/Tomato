#pragma once


namespace Tomato
{
	class Color
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
	};

	class ColorInterface
	{
	public:
		ColorInterface();
		virtual ~ColorInterface() = default;

		void SetColor(const Color& color);
		void SetRGB(const Float3& rgb);
		void SetRed(Float red);
		void SetGreen(Float green);
		void SetBlue(Float blue);
		void SetAlpha(Float alpha);

		const Color& GetColor() const;
		const Float4& GetRGBA() const;
		const Float3& GetRGB() const;
		Float GetRed() const;
		Float GetGreen() const;
		Float GetBlue() const;
		Float GetAlpha() const;

		void SetCallback(const std::function<void(const Color&)>& func);
	protected:
		std::function<void(const Color&)> m_Callback;
		Color m_Color;
	};
}
