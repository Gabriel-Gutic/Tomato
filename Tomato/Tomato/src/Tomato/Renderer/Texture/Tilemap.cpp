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

	//(0, 0); (0, 1); (1, 0); (1, 1) 
	std::array<Float2, 4> Tilemap::GetTexCoords(UInt row, UInt col, UInt rowspan, UInt colspan)
	{
		Float2 tl = Float2(row * this->GetTileWidth(), 1.0 - col * this->GetTileHeight());
		std::array<Float2, 4> arr;
		arr[0] = Float2(tl.x, tl.y - rowspan * this->GetTileHeight());
		arr[1] = tl;
		arr[2] = Float2(tl.x + colspan * this->GetTileWidth(), tl.y - rowspan * this->GetTileHeight());
		arr[3] = Float2(tl.x + colspan * this->GetTileWidth(), tl.y);
		return arr;
	}
}