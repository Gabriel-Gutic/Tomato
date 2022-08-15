#pragma once
#include "Object/Transform.h"


namespace Tomato
{
	enum class ProjectionType
	{
		Orthographic, Perspective
	};

	struct PerspectiveProjection
	{
		Float FOV;
		Float AspectRatio;
		Float Near;
		Float Far;
	};

	struct OrthographicProjection
	{
		Float Left;
		Float Right;
		Float Bottom;
		Float Top;
		Float Near;
		Float Far;
	};

	class Camera : public TransformInterface
	{
	public:
		Camera(const Float3& position = { 0.0f, 0.0f, 3.0f }, const Float3& target = {0.0f, 0.0f, 0.0f});
		~Camera() = default;

		Mat4 GetView(bool reverseY = false) const;
		Mat4 GetProjection() const;

		void MoveX(Float dist);
		void MoveY(Float dist);
		void MoveZ(Float dist);

		void SetTarget(const Float3& target);
		const Float3& GetTarget() const;

		void SetPerspectiveProjection(Float fov, Float aspectRatio, Float _near, Float _far);
		void SetOrthographicProjection(Float left, Float right, Float bottom, Float top, Float _near, Float _far);
	private:
		Float3 m_Target;

		ProjectionType m_ProjectionType;
		PerspectiveProjection m_PerspectiveProjection;
		OrthographicProjection m_OrthographicProjection;
	};
}



