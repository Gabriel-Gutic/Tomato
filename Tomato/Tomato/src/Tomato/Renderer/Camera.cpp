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
		Mat4 projection = Math::Perspective(45, 0.1f, 10.0f);
		Mat4 view = Math::LookAt(m_Position, m_Target);

		return projection * view;
	}

	void Camera::MoveX(Float dist)
	{
		m_Position.x += dist;
	}

	void Camera::MoveY(Float dist)
	{
		m_Position.y += dist;
	}

	void Camera::MoveZ(Float dist)
	{
		m_Position.z += dist;
	}
}