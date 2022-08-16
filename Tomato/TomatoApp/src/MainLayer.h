#pragma once
#include "Tomato.h"


class MainLayer : public Tomato::Layer
{
public:
	MainLayer();
	~MainLayer() = default;

	virtual void OnUpdate() override;
	virtual void OnGUI() override;
private:
	Tomato::Float4 m_TriangleColor;
	Tomato::Int m_PolygonNOS = 6;
	Tomato::Float m_CircleSmoothness = 0.5f;

	std::unordered_map<std::string, std::shared_ptr<Tomato::Texture>> m_Textures;
	std::shared_ptr<Tomato::Tilemap> m_Tilemap;

	std::shared_ptr<Tomato::Triangle> m_Triangle1;
	std::shared_ptr<Tomato::Quad> m_Quad1;
	std::shared_ptr<Tomato::Polygon> m_Polygon;
	std::shared_ptr<Tomato::Circle> m_Circle1;
};
