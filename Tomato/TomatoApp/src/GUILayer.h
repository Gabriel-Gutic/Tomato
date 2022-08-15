#pragma once
#include "Tomato.h"


class GUILayer : public Tomato::ImGuiLayer
{
public:
	GUILayer();
	~GUILayer() = default;

	virtual void OnUpdate() override;
	virtual void OnGUI() override;
	virtual void OnEvent(const Tomato::Event& e) override;
private:
	Tomato::Int m_CurrentSceneIndex = 0;

	Tomato::Float m_Speed = 0.2f;
	Tomato::Float m_FOV = 45.0f;
	Tomato::Float3 m_CameraRotation;
};

