#pragma once


namespace Tomato
{
	struct FloatComponent
	{
		Float Value;

		FloatComponent(Float value = 0) :Value(value) {}
		FloatComponent(const FloatComponent&) = default;
	};
}
