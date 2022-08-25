#pragma once
#include "Tomato.h"


class GUILayer : public Tomato::ImGuiLayer
{
public:
	GUILayer();
	~GUILayer() = default;

	virtual void OnUpdate(Tomato::Float dt) override;
	virtual void OnGUI() override;
	virtual void OnEvent(const Tomato::Event& e) override;
private:
	Tomato::Int m_CurrentSceneIndex = 0;
	Tomato::Int m_CurrentCameraProjection = 1;

	Tomato::Float m_CameraSpeed = 1.0f;
	Tomato::Float m_CameraOrthoSize = 1.0f;
	Tomato::Float m_CameraFOV = 45.0f;
	Tomato::Float3 m_CameraRotation;
	Tomato::Float4 m_BackgroundColor;
};

