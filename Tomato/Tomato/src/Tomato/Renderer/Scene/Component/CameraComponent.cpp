#include "pchTomato.h"
#include "CameraComponent.h"


namespace Tomato
{
	Mat4 CameraComponent::GetView(const TransformComponent& transform, bool reverseY) const
	{
		Float4 pos = Float4(Target - transform.Position, 1.0f);
		Float3 target = ((Quaternion::Rotation(-1 * transform.Rotation)).ToMat4() * pos).xyz;

		Mat4 view = Math::LookAt(transform.Position, target);
		if (reverseY)
		{
			Mat4 reverse(1.0f);
			reverse[1][1] = -1.0f;
			view = reverse * view;
		}
		return view;
	}

	Mat4 CameraComponent::GetProjection() const
	{
		switch (ProjectionType)
		{
		case Tomato::ProjectionType::Orthographic:
			return Math::Orthographic(Ortho.Left, Ortho.Right, Ortho.Bottom, Ortho.Top, Ortho.Near, Ortho.Far);
		case Tomato::ProjectionType::Perspective:
			return Math::Perspective(Perspective.FOV, Perspective.AspectRatio, Perspective.Near, Perspective.Far);
		}
		return Mat4(1.0f);
	}

	void CameraComponent::SetPerspectiveProjection(float fov, float aspectRatio, float _near, float _far)
	{
		ProjectionType = ProjectionType::Perspective;

		Perspective.FOV = fov;
		Perspective.AspectRatio = aspectRatio;
		Perspective.Near = _near;
		Perspective.Far = _far;
	}

	void CameraComponent::SetOrthographicProjection(float left, float right, float bottom, float top, float _near, float _far)
	{
		ProjectionType = ProjectionType::Orthographic;

		Ortho.Left = left;
		Ortho.Right = right;
		Ortho.Bottom = bottom;
		Ortho.Top = top;
		Ortho.Near = _near;
		Ortho.Far = _far;
	}
}