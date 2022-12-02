#include "pchTomato.h"
#include "Font.h"

#include <glad/glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H


namespace Tomato
{
	Font::Font(std::string_view filePath)
	{
		FT_Library ft;
		TOMATO_ASSERT(!FT_Init_FreeType(&ft), "FREETYPE: Could not init FreeType Library");
		
		FT_Face face;
		TOMATO_ASSERT(!FT_New_Face(ft, filePath.data(), 0, &face), "ERROR::FREETYPE: Failed to load font");

		FT_Set_Pixel_Sizes(face, 0, 72);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

        for (unsigned char c = 0; c < 128; c++)
        {
            // load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                TOMATO_ERROR("FREETYPE: Failed to load Glyph");
                continue;
            }
            // generate texture
            m_Chars[c].Texture = Texture::CreateShared(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer, Image::Format::Red);
            
            // now store character for later use
            m_Chars[c].Size = Int2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
            m_Chars[c].Bearing = Int2(face->glyph->bitmap_left, face->glyph->bitmap_top);
            m_Chars[c].Advance = face->glyph->advance.x;
        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
	}

    Font::~Font()
    {
    }

    const Character& Font::operator[](char chr) const
    {
        return m_Chars[chr];
    }

    const std::array<Character, 128>& Font::GetChars() const
    {
        return m_Chars;
    }

    Float2 Font::GetSize(std::string_view text, float fontSize) const
    {
        Float2 size;

        fontSize /= 1200.0f;

        float y1 = 0, y2 = 0;

        for (const auto& c : text)
        {
            const auto& ch = m_Chars[c];

            size.x += (ch.Advance >> 6) * fontSize;

            float ch_bearing_y = static_cast<float>(ch.Size.y);
            float ch_height = static_cast<float>(ch.Size.y);
            if (ch_bearing_y > y1)
                y1 = ch_bearing_y;
            if (ch_height - ch_bearing_y > y2)
                y2 = ch_height - ch_bearing_y;
        }
        size.y = (y1 + y2) * fontSize;
        return size;
    }
}