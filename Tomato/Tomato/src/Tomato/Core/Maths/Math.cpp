#include "pchTomato.h"
#include "Math.h"


namespace Tomato
{
	UInt Math::NumberOfDigits(Int number)
	{
		return UInt(log10(number)) + 1;
	}

	UInt Math::NumberOfDigits(UInt number)
	{
		return UInt(log10(number)) + 1;
	}

	UInt Math::NumberOfDigits(Long number)
	{
		return UInt(log10(number)) + 1;
	}
	UInt Math::NumberOfDigits(ULong number)
	{
		return UInt(log10(number)) + 1;
	}
	std::string Math::ToString(Int number)
	{
		return std::to_string(number);
	}

	std::string Math::ToString(UInt number)
	{
		return std::to_string(number);
	}

	std::string Math::ToString(Long number)
	{
		return std::to_string(number);
	}

	std::string Math::ToString(ULong number)
	{
		return std::to_string(number);
	}

	std::string Math::ToString(Float number, UInt precision)
	{
		Long a = Long(number);
		Float b = number - a;

		for (UInt i = 0; i < precision; i++)
			b *= 10;

		Long c = Long(b);
		while (c % 10 == 0 && c != 0)
			c /= 10;

		if (c == 0)
			return std::to_string(a);
		return std::to_string(a) + "." + std::to_string(c);
	}

	std::string Math::ToString(Double number, UInt precision)
	{
		Long a = Long(number);
		Double b = number - a;

		for (UInt i = 0; i < precision; i++)
			b *= 10;

		Long c = Long(b);
		while (c % 10 == 0 && c != 0)
			c /= 10;

		if (c == 0)
			return std::to_string(a);
		return std::to_string(a) + "." + std::to_string(c);
	}

	std::string Math::ToString(Bool value)
	{
		return value ? "True" : "False";
	}

	Float Math::Trunc(Float number, UInt precision)
	{
		UInt power = 1;
		for (UInt i = 0; i < precision; i++)
			power *= 10;
		return floorf(number * power) / (Float)power;
	}

	Double Math::Trunc(Double number, UInt precision)
	{
		UInt power = 1;
		for (UInt i = 0; i < precision; i++)
			power *= 10;
		return floor(number * power) / (Double)power;
	}

	Mat4 Math::Translate(const Mat4& matrix, const Float3& vector)
	{
		Mat4 copy = matrix;
		copy[0][3] = vector.x;
		copy[1][3] = vector.y;
		copy[2][3] = vector.z;
		return copy;
	}

	Mat4 Math::Translate(const Mat4& matrix, Float x, Float y, Float z)
	{
		return Translate(matrix, Float3(x, y, z));
	}
}


