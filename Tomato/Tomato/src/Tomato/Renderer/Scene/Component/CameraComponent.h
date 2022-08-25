#pragma once


namespace Tomato
{
	enum class ProjectionType
	{
		Orthographic = 0, Perspective = 1
	};

	namespace Component 
	{
		struct Camera
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

			Camera() = default;
			~Camera() = default;
			Camera(const Camera&) = default;

			Mat4 GetView(const Component::Transform& transform, bool reverseY = false) const;
			Mat4 GetProjection() const;

			void SetPerspectiveProjection(Float fov, Float aspectRatio, Float _near, Float _far);
			void SetOrthographicProjection(Float left, Float right, Float bottom, Float top, Float _near, Float _far);
		};
	}
}
