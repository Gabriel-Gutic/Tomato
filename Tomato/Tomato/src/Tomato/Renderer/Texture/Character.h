#pragma once
#include "Texture.h"


namespace Tomato
{
	struct Character
	{
        std::shared_ptr<Texture>  Texture;  // The glyph texture
        UInt2 Size;       // Size of glyph
        UInt2 Bearing;    // Offset from baseline to left/top of glyph
        UInt  Advance;    // Offset to advance to next glyph
	};
}
