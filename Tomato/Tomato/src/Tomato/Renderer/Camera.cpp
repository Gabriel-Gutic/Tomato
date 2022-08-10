#include "pchTomato.h"
#include "Camera.h"

#include "App.h"


namespace Tomato
{
	Camera::Camera(const Float3& position, const Float3& target)
		:m_Target(target)
	{
		SetPosition(position);
	}

	Camera::~Camera()
	{

	}

	Mat4 Camera::GetView() const
	{
		Float3 target = Quaternion::Rotate(m_Target - m_Transform.Position, -1 * m_Transform.Rotation);

		return Math::LookAt(m_Transform.Position, target);
	}

	Mat4 Camera::GetProjection() const
	{
		switch (m_ProjectionType)
		{
		case Tomato::ProjectionType::Orthographic:
			return Math::Orthographic(m_OrthographicProjection.Left, m_OrthographicProjection.Right, m_OrthographicProjection.Bottom, m_OrthographicProjection.Top, m_OrthographicProjection.Near, m_OrthographicProjection.Far);
		case Tomato::ProjectionType::Perspective:
			return Math::Perspective(m_PerspectiveProjection.FOV, m_PerspectiveProjection.AspectRatio, m_PerspectiveProjection.Near, m_PerspectiveProjection.Far);
		}
		return Mat4(1.0f);
	}

	void Camera::MoveX(Float dist)
	{
		m_Transform.Position.x += dist;
	}

	void Camera::MoveY(Float dist)
	{
		m_Transform.Position.y += dist;
	}

	void Camera::MoveZ(Float dist)
	{
		m_Transform.Position.z += dist;
	}

	void Camera::SetPerspectiveProjection(Float fov, Float aspectRatio, Float _near, Float _far)
	{
		m_ProjectionType = ProjectionType::Perspective;

		m_PerspectiveProjection.FOV = fov;
		m_PerspectiveProjection.AspectRatio = aspectRatio;
		m_PerspectiveProjection.Near = _near;
		m_PerspectiveProjection.Far = _far;
	}

	void Camera::SetOrthographicProjection(Float left, Float right, Float bottom, Float top, Float _near, Float _far)
	{
		m_ProjectionType = ProjectionType::Orthographic;

		m_OrthographicProjection.Left = left;
		m_OrthographicProjection.Right = right;
		m_OrthographicProjection.Bottom = bottom;
		m_OrthographicProjection.Top = top;
		m_OrthographicProjection.Near = _near;
		m_OrthographicProjection.Far = _far;
	}
}