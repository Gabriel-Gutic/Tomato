#pragma once


namespace Tomato
{
	struct IntComponent
	{
		Int Value;

		IntComponent(Int value = 0) :Value(value){}
		IntComponent(const IntComponent&) = default;
	};
}
