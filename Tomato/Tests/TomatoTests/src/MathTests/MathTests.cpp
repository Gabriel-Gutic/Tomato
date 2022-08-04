#include "Tomato.h"
#include "MathTests.h"

namespace Tomato::Tests
{
	void LengthTest()
	{
		Float3 vector(4, 3, 6);

		Float length = Math::Trunc(Math::Length(vector), 3);

		const Float result = 7.810f;

		TOMATO_ASSERT(length == result, "Length Test Failed!\nVector: {0}\nExpected result: {1}\nActual results: {2}", vector.ToString(), result, length);

		TOMATO_PRINT("Length Test passed!");
	}

	void NormalizeTest()
	{
		Float3 vector(4, 3, 6);

		Float3 normalized = Math::Normalize(vector);
		Float3 result(0.512, 0.384, 0.768);

		for (auto& el : normalized.list)
			el = Math::Trunc(el, 3);

		TOMATO_ASSERT((result == normalized), "Normalize Test Failed!\nVector: {0}\nExpected result: {1}\nNormalized vector: {2}", vector.ToString(), result.ToString(), normalized.ToString());

		TOMATO_PRINT("Normalize Test passed!");
	}

	void TranslateTest()
	{
		Float4 vector(4, 3, 6, 1.0f);
		Mat4 trans(1.0f);

		Float3 vector2(1, 2, 3);

		trans = Math::Translate(trans, vector2);

		Float4 translated = trans * vector;
		Float4 result(5, 5, 9,  1.0f);

		TOMATO_ASSERT((result == translated), "Translate Test Failed!\nVector: {0}\nExpected result: {1}\nTranslated vector: {2}", vector.ToString(), result.ToString(), translated.ToString());

		TOMATO_PRINT("Translate Test Passed!");
	}

	void MinorTest()
	{
		Mat4x3 mat(0.0f);

		mat[0][1] = 3.0f;
		mat[2][1] = 5.0f;
		mat[3][2] = 2.0f;
		mat[1][2] = -3.0f;
		mat[1][1] = 1.0f;

		auto minor = mat.Minor(1, 2);

		Mat3x2 result;

		result[0][1] = 3.0f;
		result[1][1] = 5.0f;

		TOMATO_ASSERT(minor == result, "Minor Test Failed!\nMinor: {0}\nExpected result: {1}", minor.ToString(), result.ToString());
	
		TOMATO_PRINT("Minor Test passed!");
	}

	void TransposeTest()
	{
		Mat4x3 mat(0.0f);

		mat[0][1] = 3.0f;
		mat[2][1] = 5.0f;
		mat[3][2] = 2.0f;
		mat[1][2] = -3.0f;
		mat[1][1] = 1.0f;

		auto transpose = Math::Transpose(mat);

		Mat3x4 result;

		result[1][0] = 3.0f;
		result[1][2] = 5.0f;
		result[2][3] = 2.0f;
		result[2][1] = -3.0f;
		result[1][1] = 1.0f;

		TOMATO_ASSERT(transpose == result, "Transpose Test Failed!\nTranspose: {0}\nExpected result: {1}", transpose.ToString(), result.ToString());

		TOMATO_PRINT("Transpose Test passed!");
	}

	void InverseTest()
	{
		Mat3 mat(0.0f);

		mat[0][0] = 1.0f;
		mat[0][2] = 2.0f;
		mat[1][1] = 1.0f;
		mat[2][1] = 3.0f;
		mat[2][2] = 2.0f;

		auto inverse = Math::Inverse(mat);

		Mat3 result;

		result[0][0] = 1.0f;
		result[0][1] = 3.0f;
		result[0][2] = -1.0f;
		result[1][1] = 1.0f;
		result[2][1] = -1.5f;
		result[2][2] = 0.5f;

		TOMATO_ASSERT(inverse == result, "Inverse Test Failed!\nInverse: {0}\nExpected result: {1}", inverse.ToString(), result.ToString());

		TOMATO_PRINT("Inverse Test passed!");
	}
}


