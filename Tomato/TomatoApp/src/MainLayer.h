#pragma once


class MainLayer : public Tomato::Layer
{
public:
	MainLayer();
	~MainLayer() = default;

	virtual void OnUpdate(Tomato::Float dt) override;
	virtual void OnGUI() override;
private:
	std::unique_ptr<Tomato::Font> m_Font;

	Tomato::Int m_PolygonNOS = 6;
	Tomato::Float m_CircleSmoothness = 0.5f;

	std::unordered_map<std::string, std::shared_ptr<Tomato::Texture>> m_Textures;
	std::shared_ptr<Tomato::Tilemap> m_Tilemap;

	std::unique_ptr<Tomato::Scene>& m_Scene;
};
