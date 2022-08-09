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

	Mat4 Camera::GetView() const
	{
		return Math::LookAt(m_Position, m_Target);
		//return Math::Transpose(Math::Translate(Float3(-0.5f, 0.0f, -1.0f)));
		//return Math::Translate(Float3(-0.5f, 0.0f, 0.0f));
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