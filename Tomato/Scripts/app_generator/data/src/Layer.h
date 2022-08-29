#pragma once


class {ProjectName}Layer : public Tomato::Layer
{
public:
    {ProjectName}Layer();
	~{ProjectName}Layer() = default;

	virtual void OnUpdate(Tomato::Float dt) override;
	virtual void OnEvent(const Tomato::Event& e) override;
	virtual void OnGUI() override;
};
