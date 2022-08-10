#pragma once


namespace Tomato
{
	struct Transform
	{
		Float3 Position;
		Float3 Scale;
		Float3 Rotation;

		Transform(const Float3& position = Float3(), const Float3& scale = Float3(1.0f, 1.0f, 1.0f), const Float3& rotation = Float3())
			:Position(position), Scale(scale), Rotation(rotation)
		{}
	};

	class TransformInterface
	{
	public:
		TransformInterface() = default;
		virtual ~TransformInterface() = default;

		void SetPosition(const Float3& position);
		void SetScale(const Float3& scale);
		void SetRotation(const Float3& rotation);
		const Float3& GetPosition() const;
		const Float3& GetScale() const;
		const Float3& GetRotation() const;

		Float3 TransformCoords(const Float3& vector) const;
	protected:
		Transform m_Transform;
	};
}
