#pragma once
#include "Texture.h"


namespace Tomato
{
	class Tilemap
	{
	public:
		Tilemap(std::string_view filePath, unsigned int tileWidth, unsigned int tileHeight);
		Tilemap(std::shared_ptr<Texture> texture, unsigned int tileWidth, unsigned int tileHeight);
	
		float GetTileWidth() const;
		float GetTileHeight() const;

		std::shared_ptr<Texture> GetTexture() const;

		std::array<Float2, 4> GetTexCoords(unsigned int row, unsigned int col, unsigned int rowspan, unsigned int colspan);
	private:
		std::shared_ptr<Texture> m_Texture;
		unsigned int m_RawTileWidth, m_RawTileHeight;
		float m_TileWidth, m_TileHeight;
	};
}