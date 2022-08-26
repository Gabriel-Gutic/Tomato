#pragma once


namespace Tomato
{
	struct TransformComponent
	{
	public:
		Float3 Position;
		Float3 Scale;
		Float3 Rotation;

		TransformComponent(const Float3& position = Float3(), const Float3& scale = Float3(1.0f, 1.0f, 1.0f), const Float3& rotation = Float3());

		Mat4 Get() const;
		void ToImGui();
	};
}
