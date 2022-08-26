#pragma once
#include "Mat.h"


namespace Tomato::Math
{
	const Float pi = acosf(-1.0f);
	const Float e = expf(1.0f);

	UInt NumberOfDigits(Int number);
	UInt NumberOfDigits(UInt number);
	UInt NumberOfDigits(Long number);
	UInt NumberOfDigits(ULong number);
	std::string ToString(Int number);
	std::string ToString(UInt number);
	std::string ToString(Long number);
	std::string ToString(ULong number);
	std::string ToString(Float number, UInt precision = 2);
	std::string ToString(Double number, UInt precision = 2);
	std::string ToString(Bool value);

	std::vector<Float2> GeneratePolygonCoords(UInt numberOfSides);
	std::vector<UInt> GeneratePolygonIndices(UInt numberOfSides);

	//Generate random int value on the closed interval [a, b]
	Int RandomInt(Int a, Int b);
	//Generate random floating-point value on the interval [a, b)
	Float RandomFloat(Float a, Float b);
	Float Trunc(Float number, UInt precision = 2);
	Double Trunc(Double number, UInt precision = 2);

	// Angles
	Float Radians(Float degrees);
	Float Degrees(Float radians);

	// Reverse
	template <typename T, size_t ROWS, size_t COLS>
	Matrix<T, COLS, ROWS> Transpose(const Matrix<T, ROWS, COLS>& mat);
	template <typename T, size_t SIZE>
	Matrix<T, SIZE, SIZE> Inverse(const Matrix<T, SIZE, SIZE>& mat);

	// Return the length of a vector
	template <typename T>
	Float Length(const T& vector);

	// Return the angle of two vectors
	template <typename T>
	Float Angle(const T& vector1, const T& vector2);

	// Return the normalized vector
	template <typename T>
	T Normalize(const T& vector);

	// Transformation Matrix
	Mat4 Translate(const Float3& vector);
	Mat4 Translate(Float x, Float y, Float z);
	Mat4 Scale(const Float3& vector);
	Mat4 Scale(Float x, Float y, Float z);
	Mat4 Rotate(const Float angle, const Float3& axe = Float3(0.0f, 0.0f, 1.0f));
	Mat4 LookAt(const Float3& position, const Float3& target);
	Mat4 Perspective(const Float fov, const Float aspect, const Float _near, const Float _far);
	Mat4 Orthographic(const Float left, const Float right, const Float bottom, const Float top, const Float _near, const Float _far);

	template<typename T, size_t ROWS, size_t COLS>
	Matrix<T, COLS, ROWS> Transpose(const Matrix<T, ROWS, COLS>& mat)
	{
		Matrix<T, COLS, ROWS> transpose;
		for (UInt i = 0; i < ROWS; i++)
			for (UInt j = 0; j < COLS; j++)
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

		for (UInt i = 0; i < SIZE; i++)
			for (UInt j = 0; j < SIZE; j++)
			{
				reverse[i][j] = pow(-1, i + j) * transpose.Minor(i, j).GetDeterminant();
			}

		return 1 / det * reverse;
	}

	template<typename T>
	Float Length(const T& vector)
	{
		Float sum = 0.0f;

		for (auto& el : vector.list)
		{
			sum += (el * el);
		}

		return sqrt(sum);
	}

	template<typename T>
	Float Angle(const T& vector1, const T& vector2)
	{
		Float l1 = Length(vector1);
		Float l2 = Length(vector2);

		if (l1 == 0 || l2 == 0)
		{
			return 0;
		}

		return acosf((vector1 * vector2) / (l1 * l2));
	}

	template<typename T>
	T Normalize(const T& vector)
	{
		Float length = Length(vector);

		if (length == 0)
			return vector;
		return (1.0f / Length(vector)) * vector;
	}

}
