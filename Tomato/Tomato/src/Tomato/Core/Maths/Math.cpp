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

	std::vector<Float2> Math::GeneratePolygonCoords(UInt numberOfSides)
	{
		TOMATO_BENCHMARKING_FUNCTION();
		TOMATO_ASSERT(numberOfSides >= 3, "You can't create a polygon with {0} sides", numberOfSides);
		Float angle = 360.0f / static_cast<Float>(numberOfSides);

		std::vector<Float2> vec;
		vec.reserve(numberOfSides + 1);

		vec.emplace_back();
		vec.emplace_back(0.0f, 0.5f);

		Float radius = 0.5f;
		Float2 center = Float2();
		Float t = acosf((vec[1].x - center.x) / radius);

		for (UInt i = 1; i < numberOfSides; i++)
		{
			vec.emplace_back(center.x + radius * cosf(t - Math::Radians(angle)), center.y + radius * sinf(t - Math::Radians(angle)));
			t -= Math::Radians(angle);
		}

		return vec;
	}

	std::vector<UInt> Math::GeneratePolygonIndices(UInt numberOfSides)
	{
		TOMATO_BENCHMARKING_FUNCTION();

		std::vector<UInt> indices;
		indices.reserve(3 * numberOfSides);
		for (UInt i = 0; i < numberOfSides; i++)
		{
			indices.push_back(0);
			indices.push_back(i + 1);
			if (i + 2 > numberOfSides)
				indices.push_back(1);
			else
				indices.push_back(i + 2);
		}

		return indices;
	}

	Int Math::RandomInt(Int a, Int b)
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<Int> distribution(a, b);
		Int random_int = distribution(mt);
		return random_int;
	}

	Float Math::RandomFloat(Float a, Float b)
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<Float> distribution(a, b);
		Float random_float = distribution(mt);
		return random_float;
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

	Float Math::Radians(Float degrees)
	{
		return degrees * (pi / 180);
	}

	Float Math::Degrees(Float radians)
	{
		return radians * (180 / pi);
	}

	Mat4 Math::Translate(const Float3& vector)
	{
		Mat4 scale(1.0f);
		scale[0][3] = vector.x;
		scale[1][3] = vector.y;
		scale[2][3] = vector.z;
		return scale;
	}

	Mat4 Math::Translate(Float x, Float y, Float z)
	{
		return Translate(Float3(x, y, z));
	}

	Mat4 Math::Scale(const Float3& vector)
	{
		Mat4 scale(1.0f);
		for (UInt i = 0; i < 3; i++)
			scale[i][i] = vector[i];
		return scale;
	}

	Mat4 Math::Scale(Float x, Float y, Float z)
	{
		return Scale(Float3(x, y, z));
	}

	Mat4 Math::Rotate(const Float angle, const Float3& axe)
	{
		Float rad = Math::Radians(angle);
		Mat4 rotate(1.0f);

		Float c = cos(rad);
		Float s = sin(rad);

		rotate[0][0] = c + axe.x * axe.x * (1 - c);
		rotate[0][1] = axe.x * axe.y * (1 - c) - axe.z * s;
		rotate[0][2] = axe.x * axe.z * (1 - c) + axe.y * s;
		rotate[1][0] = axe.y * axe.x * (1 - c) + axe.z * s;
		rotate[1][1] = c + axe.y * axe.y * (1 - c);
		rotate[1][2] = axe.y * axe.z * (1 - c) - axe.x * s;
		rotate[2][0] = axe.z * axe.x * (1 - c) - axe.y * s;
		rotate[2][1] = axe.z * axe.y * (1 - c) + axe.x * s;
		rotate[2][2] = c + axe.z * axe.z * (1 - c);

		return rotate;
	}

	Mat4 Math::LookAt(const Float3& position, const Float3& target)
	{
		Float3 direction = Math::Normalize(target - position);
		Float3 right = Math::Normalize(Float3::CrossProduct(direction, Float3(0.0f, 1.0f, 0.0f)));
		Float3 up = Float3::CrossProduct(right, direction);

		Mat4 result = Mat4(1.0f);
		for (UInt j = 0; j < 3; j++)
			result[j][0] = right[j];
		for (UInt j = 0; j < 3; j++)
			result[j][1] = up[j];
		for (UInt j = 0; j < 3; j++)
			result[j][2] = -direction[j];
		
		result[3][0] = -(right * position);
		result[3][1] = -(up * position);
		result[3][2] =  (direction * position);

		return result;
	}

	Mat4 Math::Perspective(const Float fov, const Float aspect, const Float _near, const Float _far)
	{
		Mat4 perspective = Mat4(0.0f);

		Float S = 1.0f / (tan(Radians(fov) / 2.0f));

		perspective[0][0] = S / aspect;
		perspective[1][1] = S;
		perspective[2][2] = -(_far + _near) / (_far - _near);
		perspective[2][3] = -1;
		perspective[3][2] = -((2 * _far * _near) / (_far - _near));

		return perspective;
	}

	Mat4 Math::Orthographic(const Float left, const Float right, const Float bottom, const Float top, const Float _near, const Float _far)
	{
		Mat4 ortho(1.0f);

		ortho[0][0] =  2.0f / (right - left);
		ortho[1][1] =  2.0f / (top - bottom);
		ortho[2][2] = -2.0f / (_far - _near);
		ortho[3][0] = -(right + left) / (right - left);
		ortho[3][1] = -(top + bottom) / (top - bottom);
		ortho[3][2] = -(_far + _near) / (_far - _near);

		return ortho;
	}
}


