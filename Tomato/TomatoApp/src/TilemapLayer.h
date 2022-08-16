#pragma once
#include "Tomato.h"

struct Tile
{
	Tomato::Quad Quad;
	Tomato::UInt Row, Col;
	Tomato::UInt Rowspan = 1, Colspan;

	Tile(Tomato::UInt row, Tomato::UInt col = 0, Tomato::UInt rowspan = 0, Tomato::UInt colspan = 0);
};


class TilemapLayer : public Tomato::Layer
{
public:
	TilemapLayer();
	~TilemapLayer() = default;

	virtual void OnUpdate() override;
	static void SetTilePosition(Tile& tile, Tomato::Int i, Tomato::Int j);
private:
	std::vector<Tile> m_Tiles;
	std::shared_ptr<Tomato::Tilemap> m_Tilemap;
};

