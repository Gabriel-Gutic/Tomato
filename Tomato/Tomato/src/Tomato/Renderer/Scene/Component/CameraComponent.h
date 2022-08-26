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
			Float FOV;
			Float AspectRatio;
			Float Near;
			Float Far;
		} Perspective;

		struct
		{
			Float Left;
			Float Right;
			Float Bottom;
			Float Top;
			Float Near;
			Float Far;
		} Ortho;
		Float3 Target;

		CameraComponent() = default;
		~CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;

		Mat4 GetView(const TransformComponent& transform, bool reverseY = false) const;
		Mat4 GetProjection() const;

		void SetPerspectiveProjection(Float fov, Float aspectRatio, Float _near, Float _far);
		void SetOrthographicProjection(Float left, Float right, Float bottom, Float top, Float _near, Float _far);
	};
}
