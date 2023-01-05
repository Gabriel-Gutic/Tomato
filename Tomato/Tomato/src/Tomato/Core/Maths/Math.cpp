#include "pchTomato.h"
#include "Math.h"


namespace Tomato
{
	unsigned int Math::NumberOfDigits(int number)
	{
		return (unsigned int)log10(number) + 1;
	}

	unsigned int Math::NumberOfDigits(unsigned int number)
	{
		return (unsigned int)log10(number) + 1;
	}

	unsigned int Math::NumberOfDigits(long long number)
	{
		return (unsigned int)log10(number) + 1;
	}
	unsigned int Math::NumberOfDigits(unsigned long long number)
	{
		return (unsigned int)log10(number) + 1;
	}
	std::string Math::ToString(int number)
	{
		return std::to_string(number);
	}

	std::string Math::ToString(unsigned int number)
	{
		return std::to_string(number);
	}

	std::string Math::ToString(long long number)
	{
		return std::to_string(number);
	}

	std::string Math::ToString(unsigned long long number)
	{
		return std::to_string(number);
	}

	std::string Math::ToString(float number, unsigned int precision)
	{
		long long a = (long long)number;
		float b = Abs(number - a);

		for (unsigned int i = 0; i < precision; i++)
			b *= 10;

		long long c = (long long)b;
		while (c % 10 == 0 && c != 0)
			c /= 10;

		if (c == 0)
			return std::to_string(a);
		return std::to_string(a) + "." + std::to_string(c);
	}

	std::string Math::ToString(double number, unsigned int precision)
	{
		long long a = (long long)number;
		double b = Abs(number - a);

		for (unsigned int i = 0; i < precision; i++)
			b *= 10;

		long long c = (long long)b;
		while (c % 10 == 0 && c != 0)
			c /= 10;

		if (c == 0)
			return std::to_string(a);
		return std::to_string(a) + "." + std::to_string(c);
	}

	std::string Math::ToString(bool value)
	{
		return value ? "True" : "False";
	}

	std::vector<Float2> Math::GeneratePolygonCoords(unsigned int numberOfSides)
	{
		TOMATO_BENCHMARKING_FUNCTION();
		TOMATO_ASSERT(numberOfSides >= 3, "You can't create a polygon with {0} sides", numberOfSides);
		float angle = 360.0f / static_cast<float>(numberOfSides);

		std::vector<Float2> vec;
		vec.reserve(numberOfSides + 1);

		vec.emplace_back();
		vec.emplace_back(0.0f, 0.5f);

		float radius = 0.5f;
		Float2 center = Float2();
		float t = acosf((vec[1].x - center.x) / radius);

		for (unsigned int i = 1; i < numberOfSides; i++)
		{
			vec.emplace_back(center.x + radius * cosf(t - Math::Radians(angle)), center.y + radius * sinf(t - Math::Radians(angle)));
			t -= Math::Radians(angle);
		}

		return vec;
	}

	std::vector<unsigned int> Math::GeneratePolygonIndices(unsigned int numberOfSides)
	{
		TOMATO_BENCHMARKING_FUNCTION();

		std::vector<unsigned int> indices;
		indices.reserve(3 * numberOfSides);
		for (unsigned int i = 0; i < numberOfSides; i++)
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

	int Math::RandomInt(int a, int b)
	{
		return RandomEngine::Get().RandomInt(a, b);
	}

	float Math::RandomFloat(float a, float b)
	{
		return RandomEngine::Get().RandomFloat(a, b);
	}

	float Math::Trunc(float number, unsigned int precision)
	{
		unsigned int power = 1;
		for (unsigned int i = 0; i < precision; i++)
			power *= 10;
		return floorf(number * power) / (float)power;
	}

	double Math::Trunc(double number, unsigned int precision)
	{
		unsigned int power = 1;
		for (unsigned int i = 0; i < precision; i++)
			power *= 10;
		return floor(number * power) / (double)power;
	}

	bool Math::IsNaN(float x)
	{
		return std::isnan(x);
	}

	bool Math::IsInf(float x)
	{
		return std::isinf(x);
	}

	float Math::Sqrt(float x)
	{
		if (x < 0)
			return nan;
		return sqrtf(x);
	}

	float Math::Cbrt(float x)
	{
		return cbrtf(x);
	}

	float Math::RSqrt(float x)
	{
		if (x == 0)
			return inf;
		if (x < 0)
			return nan;

		long i;
		float x2, y;
		const float threehalfs = 1.5F;

		x2 = x * 0.5F;
		y = x;
		i = *(long*)&y;								// evil floating point bit level hacking
		i = 0x5f3759df - (i >> 1);					// what the fuck? 
		y = *(float*)&i;
		y = y * (threehalfs - (x2 * y * y));		// 1st iteration
		y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

		return y;
	}

	float Math::Abs(float x)
	{
		if (x < 0.0f)
			return -x;
		return x;
	}

	float Math::Exp(float x)
	{
		return expf(x);
	}

	float Math::Log(float x)
	{
		if (x == 0)
			return -inf;
		if (x < 0)
			return nan;
		return logf(x);
	}

	float Math::Log2(float x)
	{
		if (x == 0)
			return -inf;
		if (x < 0)
			return nan;
		return log2f(x);
	}

	float Math::Log10(float x)
	{
		if (x == 0)
			return -inf;
		if (x < 0)
			return nan;
		return log10f(x);
	}

	float Math::Log(float base, float x)
	{
		if (base == 1 || base <= 0)
			return nan;
		if (x == 0)
			return -inf;
		if (x < 0)
			return nan;
		return Log(x) / Log(base);
	}

	float Math::Pow(float a, float b)
	{
		return powf(a, b);
	}

	float Math::Sin(float rad)
	{
		return sinf(rad);
	}

	float Math::Cos(float rad)
	{
		return cosf(rad);
	}

	float Math::Tan(float rad)
	{
		return tanf(rad);
	}

	float Math::ASin(float rad)
	{
		if (-1.0f > rad || rad > 1.0f)
		{
			TOMATO_ERROR("ASin invalid parameter: {0}", rad);
			return nan;
		}
		return asinf(rad);
	}

	float Math::ACos(float rad)
	{
		if (rad < -1.0f || rad > 1.0f)
		{
			TOMATO_ERROR("ACos invalid parameter: {0}", rad);
			return nan;
		}
		return acosf(rad);
	}

	float Math::ATan(float rad)
	{
		return atanf(rad);
	}

	float Math::Csc(float rad)
	{
		float _sin = Sin(rad);
		if (_sin == 0.0f)
		{
			TOMATO_ERROR("Csc invalid parameter: {0}", rad);
			return nan;
		}
		return 1.0f / _sin;
	}

	float Math::Sec(float rad)
	{
		float _cos = Cos(rad);
		if (_cos == 0.0f)
		{
			TOMATO_ERROR("Sec invalid parameter: {0}", rad);
			return nan;
		}
		return 1.0f / _cos;
	}

	float Math::Cot(float rad)
	{
		float _tan = Tan(rad);
		if (_tan == 0.0f)
		{
			TOMATO_ERROR("Cot invalid parameter: {0}", rad);
			return nan;
		}
		return 1.0f / _tan;
	}

	float Math::ACsc(float rad)
	{
		if (rad == 0.0f)
		{
			TOMATO_ERROR("ACsc invalid argument: {0}", rad);
			return nan;
		}
		return ASin(1.0f / rad);
	}

	float Math::ASec(float rad)
	{
		if (rad == 0.0f)
		{
			TOMATO_ERROR("ACsc invalid argument: {0}", rad);
			return nan;
		}
		return ACos(1.0f / rad);
	}

	float Math::ACot(float rad)
	{
		if (rad == 0.0f)
		{
			TOMATO_ERROR("ACsc invalid argument: {0}", rad);
			return nan;
		}
		return ATan(1.0f / rad);
	}

	float Math::Sinh(float rad)
	{
		return sinhf(rad);
	}

	float Math::Cosh(float rad)
	{
		return coshf(rad);
	}

	float Math::Tanh(float rad)
	{
		return tanhf(rad);
	}

	float Math::ASinh(float rad)
	{
		return asinh(rad);
	}

	float Math::ACosh(float rad)
	{
		return acosh(rad);
	}

	float Math::ATanh(float rad)
	{
		return atanh(rad);
	}

	float Math::Csch(float rad)
	{
		float _sinh = Sinh(rad);
		if (_sinh == 0.0f)
		{
			TOMATO_ERROR("Csch invalid argument: {0}", rad);
			return nan;
		}
		return 1.0f / _sinh;
	}

	float Math::Sech(float rad)
	{
		float _sech = Sech(rad);
		if (_sech == 0.0f)
		{
			TOMATO_ERROR("Sech invalid argument: {0}", rad);
			return nan;
		}
		return 1.0f / _sech;
	}

	float Math::Coth(float rad)
	{
		float _tanh = Tanh(rad);
		if (_tanh == 0.0f)
		{
			TOMATO_ERROR("Coth invalid argument: {0}", rad);
			return nan;
		}
		return 1.0f / _tanh;
	}

	float Math::ACsch(float rad)
	{
		if (rad == 0.0f)
		{
			TOMATO_ERROR("ACsch invalid argument: {0}", rad);
			return nan;
		}
		return ASinh(1.0f / rad);
	}

	float Math::ASech(float rad)
	{
		if (rad == 0.0f)
		{
			TOMATO_ERROR("ASech invalid argument: {0}", rad);
			return nan;
		}
		return ACosh(1.0f / rad);
	}

	float Math::ACoth(float rad)
	{
		if (rad == 0.0f)
		{
			TOMATO_ERROR("ACoth invalid argument: {0}", rad);
			return nan;
		}
		return ATanh(1.0f / rad);
	}

	float Math::Radians(float degrees)
	{
		return degrees * (pi / 180);
	}

	float Math::Degrees(float radians)
	{
		return radians * (180 / pi);
	}

	Mat4 Math::Transpose(const Mat4& mat)
	{
		Mat4 transpose;
		for (unsigned int i = 0; i < 4; i++)
			for (unsigned int j = 0; j < 4; j++)
				transpose[j][i] = mat[i][j];
		return transpose;
	}

	Mat4 Math::Inverse(const Mat4& mat)
	{
		float det = mat.GetDeterminant();

		TOMATO_ASSERT(det != 0, "The determinant can not be null");

		Mat4 transpose = Transpose(mat);
		Mat4 reverse;

		for (unsigned int i = 0; i < 4; i++)
			for (unsigned int j = 0; j < 4; j++)
			{
				reverse[i][j] = Math::Pow(-1, i + j) * transpose.Minor(i, j).GetDeterminant();
			}

		return 1 / det * reverse;
	}

	Mat4 Math::Translate(const Float3& vector)
	{
		Mat4 scale(1.0f);
		scale[0][3] = vector.x;
		scale[1][3] = vector.y;
		scale[2][3] = vector.z;
		return scale;
	}

	Mat4 Math::Translate(float x, float y, float z)
	{
		return Translate(Float3(x, y, z));
	}

	Mat4 Math::Scale(const Float3& vector)
	{
		Mat4 scale(1.0f);
		for (unsigned int i = 0; i < 3; i++)
			scale[i][i] = vector[i];
		return scale;
	}

	Mat4 Math::Scale(float x, float y, float z)
	{
		return Scale(Float3(x, y, z));
	}

	Mat4 Math::Rotate(const float angle, const Float3& axe)
	{
		float rad = Math::Radians(angle);
		Mat4 rotate(1.0f);

		float c = cos(rad);
		float s = sin(rad);

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
		for (unsigned int j = 0; j < 3; j++)
			result[j][0] = right[j];
		for (unsigned int j = 0; j < 3; j++)
			result[j][1] = up[j];
		for (unsigned int j = 0; j < 3; j++)
			result[j][2] = -direction[j];
		
		result[3][0] = -Float3::DotProduct(right, position);
		result[3][1] = -Float3::DotProduct(up, position);
		result[3][2] = Float3::DotProduct(direction, position);

		return result;
	}

	Mat4 Math::Perspective(const float fov, const float aspect, const float _near, const float _far)
	{
		Mat4 perspective = Mat4(0.0f);

		float S = 1.0f / (tan(Radians(fov) / 2.0f));

		perspective[0][0] = S / aspect;
		perspective[1][1] = S;
		perspective[2][2] = -(_far + _near) / (_far - _near);
		perspective[2][3] = -1;
		perspective[3][2] = -((2 * _far * _near) / (_far - _near));

		return perspective;
	}

	Mat4 Math::Orthographic(const float left, const float right, const float bottom, const float top, const float _near, const float _far)
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


