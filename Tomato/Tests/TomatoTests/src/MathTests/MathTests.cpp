#include "Tomato.h"
#include "MathTests.h"

namespace Tomato::Tests
{
	void LengthTest()
	{
		Float3 vector(4, 3, 6);

		Float length = Math::Length(vector);

		TOMATO_ASSERT(length == 7.810249675906654, "Length Test Failed!\nVector: {0}\nExpected result: {1}\nActual results: {2}", vector.ToString(), 7.810249675906654, length);

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
}


