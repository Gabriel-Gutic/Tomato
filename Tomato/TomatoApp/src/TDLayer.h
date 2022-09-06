#pragma once


class TDLayer : public Tomato::Layer
{
public:
	TDLayer();
	~TDLayer() = default;

	virtual void OnUpdate(float dt) override;
private:
	std::unordered_map<std::string, std::shared_ptr<Tomato::Texture>> m_Textures;
	//std::shared_ptr<Tomato::Cube> m_Cube;
	Tomato::Timer m_Timer;
};

