#pragma once
#include "Component.h"


namespace Tomato
{
	class Color : public Component
	{
	public:
		
		Color(Float r = 1.0f, Float g = 1.0f, Float b = 1.0f, Float a = 1.0f);
		Color(const Float3& rgb);
		Color(const Float4& rgba);
		Color(const Color& other);
		~Color() = default;

		void SetRGBA(const Float4& rgba);
		void SetRGB(const Float3& rgb);
		void SetRed(Float red);
		void SetGreen(Float green);
		void SetBlue(Float blue);
		void SetAlpha(Float alpha);

		const Float4& GetRGBA() const;
		const Float3& GetRGB() const;
		Float GetRed() const;
		Float GetGreen() const;
		Float GetBlue() const;
		Float GetAlpha() const;

		Color& operator=(const Color& other);

		virtual void ToImGui() override;
		virtual std::string GetType() const override;

		Float* ToPtr();
	private:
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
	};
}
