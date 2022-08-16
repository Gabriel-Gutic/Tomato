#include "pchTomato.h"
#include "Tilemap.h"


namespace Tomato
{
	Tilemap::Tilemap(std::string_view filePath, UInt tileWidth, UInt tileHeight)
		:Tilemap(Texture::Create(filePath), tileWidth, tileHeight)
	{
	}

	Tilemap::Tilemap(std::shared_ptr<Texture> texture, UInt tileWidth, UInt tileHeight)
		:m_Texture(texture), m_RawTileWidth(tileWidth), m_RawTileHeight(tileHeight)
	{
		m_TileWidth = (Float)m_RawTileWidth / (Float)m_Texture->GetWidth();
		m_TileHeight = (Float)m_RawTileHeight / (Float)m_Texture->GetHeight();
	}

	Float Tilemap::GetTileWidth() const
	{
		return m_TileWidth;
	}

	Float Tilemap::GetTileHeight() const
	{
		return m_TileHeight;
	}

	std::shared_ptr<Texture> Tilemap::GetTexture() const
	{
		return m_Texture;
	}
}