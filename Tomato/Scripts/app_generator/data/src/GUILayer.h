#pragma once


class GUILayer : public Tomato::ImGuiLayer
{
public:
	GUILayer();
	~GUILayer() = default;

	virtual void OnUpdate(Tomato::Float dt) override;
	virtual void OnGUI() override;
	virtual void OnEvent(const Tomato::Event& e) override;
private:
};

