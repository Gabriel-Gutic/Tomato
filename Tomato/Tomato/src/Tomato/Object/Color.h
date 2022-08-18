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

		Float* ToPtr();
	};

	class ColorInterface
	{
	public:
		ColorInterface();
		ColorInterface(const ColorInterface& ci);
		virtual ~ColorInterface() = default;

		void SetColor(const Color& color);
		void SetRGB(const Float3& rgb);
		void SetRed(Float red);
		void SetGreen(Float green);
		void SetBlue(Float blue);
		void SetAlpha(Float alpha);

		Color& GetColor();
		const Color& GetColor() const;
		const Float4& GetRGBA() const;
		const Float3& GetRGB() const;
		Float GetRed() const;
		Float GetGreen() const;
		Float GetBlue() const;
		Float GetAlpha() const;
	protected:
		Color m_Color;
	};
}


namespace YAML
{
	template<>
	struct convert<Tomato::Color> {
		static Node encode(const Tomato::Color& color) {
			Node node;
			node["Red"] = color.Red;
			node["Green"] = color.Green;
			node["Blue"] = color.Blue;
			node["Alpha"] = color.Alpha;
			return node;
		}
		static bool decode(const Node& node, Tomato::Color& color) {
			if (!node.IsMap()) {
				return false;
			}
			if (node["Red"])
				color.Red = node["Red"].as<Tomato::Float>();
			if (node["Green"])
				color.Green = node["Green"].as<Tomato::Float>();
			if (node["Blue"])
				color.Blue = node["Blue"].as<Tomato::Float>();
			if (node["Alpha"])
				color.Alpha = node["Alpha"].as<Tomato::Float>();
			return true;
		}
	};
}
