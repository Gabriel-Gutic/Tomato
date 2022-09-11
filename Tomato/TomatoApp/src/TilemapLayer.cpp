#include "pchTomatoApp.h"
#include "TilemapLayer.h"


TilemapLayer::TilemapLayer()
{
	Tomato::App::GetScenes()["Tilemap Scene"]->GetCamera()->GetComponent<Tomato::TransformComponent>().Position = Tomato::Float3(0.0f, 0.0f, 12.0f);

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

void TilemapLayer::OnUpdate(float dt)
{
	for (const auto& tile : m_Tiles)
		Tomato::Renderer::Draw(tile.Quad, m_Tilemap, tile.Row, tile.Col, tile.Rowspan, tile.Colspan);
}

void TilemapLayer::SetTilePosition(Tile& tile, int i, int j)
{
	Tomato::Float3 pos;
	pos.x = (float)i + (float)tile.Rowspan / 2.0f;
	pos.y = (float)j - (float)tile.Colspan / 2.0f;
	tile.Quad.GetComponent<Tomato::TransformComponent>().Position = pos;
}

Tile::Tile(unsigned int row, unsigned int col, unsigned int rowspan, unsigned int colspan)
	:Row(row), Col(col), Rowspan(rowspan), Colspan(colspan)
{
	Quad.AddComponent<Tomato::TransformComponent>().Scale = Tomato::Float3((float)Rowspan, (float)Colspan, 1.0f);
}
