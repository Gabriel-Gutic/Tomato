#pragma once
#include "Texture.h"


namespace Tomato
{
	struct Character
	{
        std::shared_ptr<Texture>  Texture;  // The glyph texture
        Int2 Size;       // Size of glyph
        Int2 Bearing;    // Offset from baseline to left/top of glyph
        int  Advance;    // Offset to advance to next glyph
	};
}
