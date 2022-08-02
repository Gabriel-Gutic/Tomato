#pragma once


namespace Tomato
{
	class Camera
	{
	public:
		Camera(const Float3 position = { 0.0f, 0.0f, 3.0f }, const Float3 target = {0.0f, 0.0f, 0.0f});
		~Camera();

		Mat4 Update() const;
	private:
		Float3 m_Position;
		Float3 m_Target;
	};
}



