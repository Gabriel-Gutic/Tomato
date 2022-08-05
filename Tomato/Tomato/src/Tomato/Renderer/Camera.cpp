#include "pchTomato.h"
#include "Camera.h"

#include "App.h"


namespace Tomato
{
	Camera::Camera(const Float3& position, const Float3& target)
		:m_Position(position), m_Target(target)
	{
	}

	Camera::~Camera()
	{

	}

	Mat4 Camera::Update() const
	{
		switch (m_ProjectionType)
		{
		case Tomato::ProjectionType::Orthographic:
			//TODO: Implement Orthographic Camera
			break;
		case Tomato::ProjectionType::Perspective:
			Mat4 view = Math::LookAt(m_Position, m_Target);
			Mat4 projection = Math::Perspective(m_PerspectiveProjection.FOV, m_PerspectiveProjection.AspectRatio, m_PerspectiveProjection.Near, m_PerspectiveProjection.Far);

			return projection * view;
		}
		return Mat4();
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

	void Camera::SetPerspectiveProjection(Float fov, Float aspectRatio, Float _near, Float _far)
	{
		m_ProjectionType = ProjectionType::Perspective;

		m_PerspectiveProjection.FOV = fov;
		m_PerspectiveProjection.AspectRatio = aspectRatio;
		m_PerspectiveProjection.Near = _near;
		m_PerspectiveProjection.Far = _far;
	}
}