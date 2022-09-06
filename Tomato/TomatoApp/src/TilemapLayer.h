#pragma once

struct Tile
{
	Tomato::Entity Quad;
	unsigned int Row, Col;
	unsigned int Rowspan = 1, Colspan;

	Tile(unsigned int row, unsigned int col = 0, unsigned int rowspan = 0, unsigned int colspan = 0);
};


class TilemapLayer : public Tomato::Layer
{
public:
	TilemapLayer();
	~TilemapLayer() override = default;

	virtual void OnUpdate(float dt) override;
	static void SetTilePosition(Tile& tile, int i, int j);
private:
	std::vector<Tile> m_Tiles;
	std::shared_ptr<Tomato::Tilemap> m_Tilemap;
};

