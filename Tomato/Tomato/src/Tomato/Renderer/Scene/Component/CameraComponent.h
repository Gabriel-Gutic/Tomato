#pragma once


namespace Tomato
{
	enum class ProjectionType
	{
		Orthographic = 0, Perspective = 1
	};

	struct CameraComponent
	{
		ProjectionType ProjectionType;
		struct
		{
			float FOV;
			float AspectRatio;
			float Near;
			float Far;
		} Perspective;

		struct
		{
			float Left;
			float Right;
			float Bottom;
			float Top;
			float Near;
			float Far;
		} Ortho;
		Float3 Target;

		CameraComponent() = default;
		~CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;

		Mat4 GetView(const TransformComponent& transform, bool reverseY = false) const;
		Mat4 GetProjection() const;

		void SetPerspectiveProjection(float fov, float aspectRatio, float _near, float _far);
		void SetOrthographicProjection(float left, float right, float bottom, float top, float _near, float _far);
	};
}
