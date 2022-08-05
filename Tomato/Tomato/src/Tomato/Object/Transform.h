#pragma once


namespace Tomato
{
	struct Transform
	{
		Float3 Position;
		Float3 Scale;
		Float3 Rotation;

		Transform(const Float3& position = Float3(), const Float3& scale = Float3(1.0f, 1.0f, 1.0f), const Float3& rotation = Float3())
			:Position(position), Scale(scale), Rotation(rotation)
		{}
	};
}
