#include "pchTomato.h"
#include "Tilemap.h"


namespace Tomato
{
	Tilemap::Tilemap(std::string_view filePath, unsigned int tileWidth, unsigned int tileHeight)
		:Tilemap(Texture::CreateShared(filePath), tileWidth, tileHeight)
	{
	}

	Tilemap::Tilemap(std::shared_ptr<Texture> texture, unsigned int tileWidth, unsigned int tileHeight)
		:m_Texture(texture), m_RawTileWidth(tileWidth), m_RawTileHeight(tileHeight)
	{
		m_TileWidth = (float)m_RawTileWidth / (float)m_Texture->GetWidth();
		m_TileHeight = (float)m_RawTileHeight / (float)m_Texture->GetHeight();
	}

	float Tilemap::GetTileWidth() const
	{
		return m_TileWidth;
	}

	float Tilemap::GetTileHeight() const
	{
		return m_TileHeight;
	}

	std::shared_ptr<Texture> Tilemap::GetTexture() const
	{
		return m_Texture;
	}

	//(0, 0); (0, 1); (1, 0); (1, 1) 
	std::array<Float2, 4> Tilemap::GetTexCoords(unsigned int row, unsigned int col, unsigned int rowspan, unsigned int colspan)
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