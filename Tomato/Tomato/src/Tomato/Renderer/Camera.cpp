#include "pchTomato.h"
#include "Camera.h"


namespace Tomato
{
	Camera::Camera(const Float3 position, const Float3 target)
		:m_Position(position), m_Target(target)
	{
	}

	Camera::~Camera()
	{

	}

	Mat4 Camera::Update() const
	{
		Mat4 perspective = Math::Perspective(90, 0.5f, 100.0f);
		Mat4 view = Math::LookAt(m_Position, m_Target);

		return perspective * view;
	}
}