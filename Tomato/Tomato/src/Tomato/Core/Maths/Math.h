#pragma once
#include "Mat.h"


namespace Tomato::Math
{
	const Float pi = acos(-1);
	const Float e = exp(1);

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

	// Return the normalized vector
	template <typename T>
	T Normalize(const T& vector);

	// Create a translation matrix
	Mat4 Translate(const Mat4& matrix, const Float3& vector);
	Mat4 Translate(const Mat4& matrix, Float x, Float y, Float z);
	Mat4 LookAt(const Float3& position, const Float3& target);
	Mat4 Perspective(Float fov, Float _near, Float _far);

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
	T Normalize(const T& vector)
	{
		Float length = Length(vector);

		if (length == 0)
			return vector;
		return (1.0f / Length(vector)) * vector;
	}

}
