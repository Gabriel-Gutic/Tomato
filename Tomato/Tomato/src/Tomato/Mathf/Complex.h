#pragma once
#include <iostream>


namespace Tomato
{
	class Complex
	{
	public:
		static const Complex Nan;
		static const Complex Inf;
	public:
		Complex(float real = 0.0f, float imaginary = 0.0f);
		Complex(const Complex& other);
		Complex& operator=(const Complex& other);
		virtual ~Complex() = default;

		float GetReal() const;
		float GetImaginary() const;
		void SetReal(float real);
		void SetImaginary(float imag);

		float GetArgument() const;
		float GetModulus() const;
		float GetModulusSquared() const;
		void SetArgument(float theta);
		void SetModulus(float ro);

		Complex GetReverse() const;
		Complex GetConjugate() const;
		bool IsInf() const;
		bool IsNan() const;

		std::string ToString() const;
		explicit operator float() const;

		friend std::ostream& operator<<(std::ostream& os, const Complex& z);

		Complex operator-();
		friend Complex operator+(const Complex& z1, const Complex& z2);
		friend Complex operator-(const Complex& z1, const Complex& z2);
		friend Complex operator*(const Complex& z1, const Complex& z2);
		friend Complex operator/(const Complex& z1, const Complex& z2);

		friend bool operator==(const Complex& z1, const Complex& z2);
		friend bool operator!=(const Complex& z1, const Complex& z2);
	public:
		// ro -> the modulus of the complex number
		// theta -> the argument of the complex number
		static Complex CreateFromPolar(float theta, float ro = 1.0f);
	private:
		float m_Real;
		float m_Imaginary;
	};

}

