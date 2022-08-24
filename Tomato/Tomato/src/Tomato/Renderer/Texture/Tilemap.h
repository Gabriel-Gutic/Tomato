#pragma once
#include "Texture.h"


namespace Tomato
{
	class Tilemap
	{
	public:
		Tilemap(std::string_view filePath, UInt tileWidth, UInt tileHeight);
		Tilemap(std::shared_ptr<Texture> texture, UInt tileWidth, UInt tileHeight);
	
		Float GetTileWidth() const;
		Float GetTileHeight() const;

		std::shared_ptr<Texture> GetTexture() const;

		std::array<Float2, 4> GetTexCoords(UInt row, UInt col, UInt rowspan, UInt colspan);
	private:
		std::shared_ptr<Texture> m_Texture;
		UInt m_RawTileWidth, m_RawTileHeight;
		Float m_TileWidth, m_TileHeight;
	};
}