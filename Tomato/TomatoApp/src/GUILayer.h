#pragma once


class GUILayer : public Tomato::ImGuiLayer
{
public:
	GUILayer();
	~GUILayer() = default;

	virtual void OnUpdate(float dt) override;
	virtual void OnGUI() override;
	virtual void OnEvent(const Tomato::Event& e) override;
private:
	int m_CurrentSceneIndex = 0;
	int m_CurrentCameraProjection = 1;

	float m_CameraSpeed = 3.0f;
	float m_CameraOrthoSize = 1.0f;
	float m_CameraFOV = 45.0f;
	Tomato::Float4 m_BackgroundColor;
};