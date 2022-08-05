#pragma once


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

	class Camera
	{
	public:
		Camera(const Float3& position = { 0.0f, 0.0f, 3.0f }, const Float3& target = {0.0f, 0.0f, 0.0f});
		~Camera();

		Mat4 Update() const;

		void MoveX(Float dist);
		void MoveY(Float dist);
		void MoveZ(Float dist);

		void SetPerspectiveProjection(Float fov, Float aspectRatio, Float _near, Float _far);
	private:
		Float3 m_Position;
		Float3 m_Target;

		ProjectionType m_ProjectionType;
		PerspectiveProjection m_PerspectiveProjection;
	};
}



