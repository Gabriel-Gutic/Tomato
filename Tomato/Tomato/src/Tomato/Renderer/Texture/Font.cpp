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
		TOMATO_ASSERT(!FT_Init_FreeType(&ft), "ERROR::FREETYPE: Could not init FreeType Library");
		
		FT_Face face;
		TOMATO_ASSERT(!FT_New_Face(ft, filePath.data(), 0, &face), "ERROR::FREETYPE: Failed to load font");

		FT_Set_Pixel_Sizes(face, 0, 72);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

        for (unsigned char c = 0; c < 128; c++)
        {
            // load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                TOMATO_ERROR("ERROR::FREETYTPE: Failed to load Glyph");
                continue;
            }
            // generate texture
            m_Chars[c].Texture = std::make_shared<Texture>(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer, GL_RED);
            
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
}