#pragma once
#include "Component.h"


namespace Tomato
{
	struct Transform : public Component
	{
	public:
		Transform(const Float3& position = Float3(), const Float3& scale = Float3(1.0f, 1.0f, 1.0f), const Float3& rotation = Float3());

		void SetPosition(const Float3& position);
		void SetScale(const Float3& scale);
		void SetRotation(const Float3& rotation);
		const Float3& GetPosition() const;
		const Float3& GetScale() const;
		const Float3& GetRotation() const;
		Float3& GetPosition();
		Float3& GetScale();
		Float3& GetRotation();

		Float3 Apply(const Float3& vector) const;
		virtual void ToImGui() override;
		virtual std::string GetType() const override;
	private:
		Float3 m_Position;
		Float3 m_Scale;
		Float3 m_Rotation;
	};
}
