#include "TilemapLayer.h"


TilemapLayer::TilemapLayer()
{
	Tomato::App::GetScenes()["Tilemap Scene"]->GetCamera()->SetPosition(Tomato::Float3(0.0f, 0.0f, 12.0f));

	m_Tilemap = std::make_shared<Tomato::Tilemap>("assets/images/TX Tileset Grass.png", 16, 16);

	m_Tiles.emplace_back(1, 1, 3, 3);
	SetTilePosition(m_Tiles[0], -4, 4);
	m_Tiles.emplace_back(7, 4, 2, 2);
	SetTilePosition(m_Tiles[1], 1, 1);
	m_Tiles.emplace_back(7, 4, 2, 2);
	SetTilePosition(m_Tiles[2], -1, 1);
	m_Tiles.emplace_back(7, 4, 2, 2);
	SetTilePosition(m_Tiles[3], -3, 1);
	m_Tiles.emplace_back(1, 1, 3, 3);
	SetTilePosition(m_Tiles[4], -1, 4);
}

void TilemapLayer::OnUpdate()
{
	for (const auto& tile : m_Tiles)
		Tomato::Renderer::Draw(tile.Quad, m_Tilemap, tile.Row, tile.Col, tile.Rowspan, tile.Colspan);
}

void TilemapLayer::SetTilePosition(Tile& tile, Tomato::Int i, Tomato::Int j)
{
	Tomato::Float3 pos;
	pos.x = (Tomato::Float)i + (Tomato::Float)tile.Rowspan / 2.0f;
	pos.y = (Tomato::Float)j - (Tomato::Float)tile.Colspan / 2.0f;
	tile.Quad.SetPosition(pos);
}

Tile::Tile(Tomato::UInt row, Tomato::UInt col, Tomato::UInt rowspan, Tomato::UInt colspan)
	:Row(row), Col(col), Rowspan(rowspan), Colspan(colspan)
{
	Quad.SetScale(Tomato::Float3((Tomato::Float)Rowspan, (Tomato::Float)Colspan, 1.0f));
}
