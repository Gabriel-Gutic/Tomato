#pragma once
#include "Mat.h"


namespace Tomato::Math
{
	const float pi = acosf(-1.0f);
	const float e = expf(1.0f);

	unsigned int NumberOfDigits(int number);
	unsigned int NumberOfDigits(unsigned int number);
	unsigned int NumberOfDigits(long long number);
	unsigned int NumberOfDigits(unsigned long long number);
	std::string ToString(int number);
	std::string ToString(unsigned int number);
	std::string ToString(long long number);
	std::string ToString(unsigned long long number);
	std::string ToString(float number, unsigned int precision = 2);
	std::string ToString(double number, unsigned int precision = 2);
	std::string ToString(bool value);

	std::vector<Float2> GeneratePolygonCoords(unsigned int numberOfSides);
	std::vector<unsigned int> GeneratePolygonIndices(unsigned int numberOfSides);

	//Generate random int value on the closed interval [a, b]
	int RandomInt(int a, int b);
	//Generate random floating-point value on the interval [a, b)
	float RandomFloat(float a, float b);
	float Trunc(float number, unsigned int precision = 2);
	double Trunc(double number, unsigned int precision = 2);

	float Exp(float x);
	float Sqrt(float x);
	float RSqrt(float x);
	float Log(float x);
	float Log2(float x);
	float Log10(float x);
	float Log(float base, float x);
	float Pow(float a, float b);

	// Trigonometric Functions
	float Sin(float rad);
	float Cos(float rad);
	float Tan(float rad);

	float ASin(float rad);
	float ACos(float rad);
	float ATan(float rad);

	float Csc(float rad);
	float Sec(float rad);
	float Cot(float rad);

	float ACsc(float rad);
	float ASec(float rad);
	float ACot(float rad);

	float Sinh(float rad);
	float Cosh(float rad);
	float Tanh(float rad);

	float ASinh(float rad);
	float ACosh(float rad);
	float ATanh(float rad);

	float Csch(float rad);
	float Sech(float rad);
	float Coth(float rad);

	float ACsch(float rad);
	float ASech(float rad);
	float ACoth(float rad);

	// Angles
	float Radians(float degrees);
	float Degrees(float radians);

	// Reverse
	template <typename T, size_t ROWS, size_t COLS>
	Matrix<T, COLS, ROWS> Transpose(const Matrix<T, ROWS, COLS>& mat);
	template <typename T, size_t SIZE>
	Matrix<T, SIZE, SIZE> Inverse(const Matrix<T, SIZE, SIZE>& mat);

	// Return the length of a vector
	template <typename T>
	float Length(const T& vector);

	// Return the angle of two vectors
	template <typename T>
	float Angle(const T& vector1, const T& vector2);

	// Return the normalized vector
	template <typename T>
	T Normalize(const T& vector);

	// Transformation Matrix
	Mat4 Translate(const Float3& vector);
	Mat4 Translate(float x, float y, float z);
	Mat4 Scale(const Float3& vector);
	Mat4 Scale(float x, float y, float z);
	Mat4 Rotate(const float angle, const Float3& axe = Float3(0.0f, 0.0f, 1.0f));
	Mat4 LookAt(const Float3& position, const Float3& target);
	Mat4 Perspective(const float fov, const float aspect, const float _near, const float _far);
	Mat4 Orthographic(const float left, const float right, const float bottom, const float top, const float _near, const float _far);

	template<typename T, size_t ROWS, size_t COLS>
	Matrix<T, COLS, ROWS> Transpose(const Matrix<T, ROWS, COLS>& mat)
	{
		Matrix<T, COLS, ROWS> transpose;
		for (unsigned int i = 0; i < ROWS; i++)
			for (unsigned int j = 0; j < COLS; j++)
				transpose[j][i] = mat[i][j];
		return transpose;
	}

	template<typename T, size_t SIZE>
	Matrix<T, SIZE, SIZE> Inverse(const Matrix<T, SIZE, SIZE>& mat)
	{
		T det = mat.GetDeterminant();

		TOMATO_ASSERT(det != 0, "The determinant can not be null");

		Matrix<T, SIZE, SIZE> transpose = Transpose(mat);
		Matrix<T, SIZE, SIZE> reverse;

		for (unsigned int i = 0; i < SIZE; i++)
			for (unsigned int j = 0; j < SIZE; j++)
			{
				reverse[i][j] = pow(-1, i + j) * transpose.Minor(i, j).GetDeterminant();
			}

		return 1 / det * reverse;
	}

	template<typename T>
	float Length(const T& vector)
	{
		float sum = 0.0f;

		for (auto& el : vector.list)
		{
			sum += (el * el);
		}

		return sqrt(sum);
	}

	template<typename T>
	float Angle(const T& vector1, const T& vector2)
	{
		float l1 = Length(vector1);
		float l2 = Length(vector2);

		if (l1 == 0 || l2 == 0)
		{
			return 0;
		}

		return acosf((vector1 * vector2) / (l1 * l2));
	}

	template<typename T>
	T Normalize(const T& vector)
	{
		float length = Length(vector);

		if (length == 0)
			return vector;
		return (1.0f / Length(vector)) * vector;
	}

}
