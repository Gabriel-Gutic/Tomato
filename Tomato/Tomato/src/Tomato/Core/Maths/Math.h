#pragma once
#include "Mat.h"


namespace Tomato::Math
{
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

	//Return the length of a vector
	template <typename T>
	Float Length(const T& vector);

	//Return the normalized vector
	template <typename T>
	T Normalize(const T& vector);

	//Create a translation matrix
	Mat4 Translate(const Mat4& matrix, const Float3& vector);
	Mat4 Translate(const Mat4& matrix, Float x, Float y, Float z);

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
		return (1.0f / Length(vector)) * vector;
	}

}
