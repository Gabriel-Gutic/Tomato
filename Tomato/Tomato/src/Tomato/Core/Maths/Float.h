#pragma once
#include "Vec.h"


namespace Tomato
{
	typedef float Float;
	typedef double Double;

	Vec2h(Float)
	Vec3h(Float)
	Vec4h(Float)
	Vec2h(Double)
	Vec3h(Double)
	Vec4h(Double)
}


namespace YAML
{
	Vec2Node(Float)
	Vec3Node(Float)
	Vec4Node(Float)
	Vec2Node(Double)
	Vec3Node(Double)
	Vec4Node(Double)
}
